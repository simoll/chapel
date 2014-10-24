#include "qbuffer.h"

#define QSTRING_TAG_TYPE_BITS 2
#define QSTRING_TAG_UTF8_MASK 0x20
#define QSTRING_TAG_SMALL_LEN_MASK 0x1f
#define QSTRING_TAG_SMALL_MAXLEN 23
#define QSTRING_TAG_NOT_SMALL_LEN_MASK 0xe0

#define QSTRING_MAX_UNUSED_BUFFER 8192

typedef enum {
  QSTRING_TAG_TYPE_SMALL = 0,
  QSTRING_TAG_TYPE_PTR = 1,
  QSTRING_TAG_TYPE_BUFFER = 2,
} qstring_type_t;

// Experiments with calling a routine passing a structure
// on x86_64 indicate that 2-words, 3-words, and 4-words
// have similar performance in calling and accessing
// only part of the structure. Using more of the structure
// is what costs.
/*
 * String complexity:
 *  indexing (by byte)      O(1)
 *  indexing (by character) O(log n) / O(n)
 *  append a byte           O(1) / O(n)
 *  copy (local)            O(sqrt(n)) / O(1)
 *  copy (remote)           O(n)
 *  replace/insert/delete   O(n)
 *  concatenate             O(n)
 *
 * String space overhead    O(sqrt(n))
 *
 * Strings are implemented as resizeable arrays
 * with O(sqrt(n)) blocks. Each qstring_t
 * is 24 bytes. Strings < 24 bytes are stored
 * right in the qstring_t. Otherwise, we can
 * have a pointer to some allocated memory,
 * (like a C string but including a length),
 * or a qbuffer-backed string that supports
 * efficient appending with O(sqrt(n)) extra
 * space.
 *
 */

typedef struct qstring_s {
  union {
    struct qstring_words_s {
      uint64_t word1;
      uint64_t word2;
      uint64_t word3;
    } words;
    struct qstring_small_s {
      unsigned char data[QSTRING_TAG_SMALL_MAXLEN];
      uint8_t tag; // from least significant:
                   //   7  6  5  4  3  2  1  0
                   // | type |nc|    24-len   |
                   // nc == not character data.
    } small;
    struct qstring_ptr_s {
      // Use this version for constant program data
      // Since the program image is the same everywhere,
      // we don't need to include a locale, and
      // reference counting is unnecessary.
      const char* data; // immutable, never freed
      int64_t len;
      uint16_t unused1;
      uint16_t unused2;
      uint16_t unused3;
      uint8_t unused4;
      uint8_t tag;
    } ptr;
    struct {
      // If we dynamically allocate a flat string, we use
      // this version, but cannot append.
      qbytes_t* bytes; // pointer, length immutable
      int64_t locale;
      uint16_t unused1;
      uint16_t unused2;
      uint16_t unused3;
      uint8_t immutable; // if we ever share the qbytes, immutable=1
                         // if we have exclusive access
                         //  (ie refcnt has always been ==1) immutable=0
                         // and the qbytes->data can be mutated in place.
      uint8_t tag;
    } bytes;
    struct {
      // Any string that we have appended to is in this format.
      qbuffer_t* buffer; // NOT immutable - owned by this string!
                         // must be copied... deallocated when done.
                         // BUT, qbytes data in buffer is write-once.
      int64_t locale;
      uint16_t unused1;
      uint16_t unused2;
      uint16_t unused3;
      uint8_t unused4;
      uint8_t tag;
    } buffer;
  } u;
} qstring_t;

static inline
qstring_type_t qstring_type(uint8_t tag)
{
  return tag >> (8-QSTRING_TAG_TYPE_BITS); 
}
static inline
int32_t qstring_ptr_skip_start(qstring_t arg)
{
  return arg.skip_start | ( (arg.skip_truncate_hi & 0xf0) << 4 );
}
static inline
int32_t qstring_ptr_truncate_end(qstring_t arg)
{
  return arg.truncate_end | ( (arg.skip_truncate_hi & 0x0f) << 8 );
}

static inline
int64_t qstring_length(qstring_t arg)
{
  qstring_type_t type = qstring_type(arg.small.tag);
  if( type == QSTRING_TAG_TYPE_SMALL ) {
    return QSTRING_TAG_SMALL_MAXLEN - (arg.small.tag & QSTRING_TAG_SMALL_LEN_MASK);
  } else if( type == QSTRING_TAG_TYPE_PTR ) {
    return arg.ptr.bytes->length - qstring_ptr_skip_start(arg)
                                 - qstring_ptr_truncate_end(arg);
  } else {
    return qbuffer_len(arg.buffer.buffer);
  }
}

int64_t qstring_buffer_size(qstring_t arg, int64_t *num_parts)
{
  // How much buffer space is used by the qstring?
  qstring_type_t type = qstring_type(arg.small.tag);
  if( type == QSTRING_TAG_TYPE_SMALL ) {
    *num_parts = 0;
    return QSTRING_TAG_SMALL_MAXLEN;
  } else if( type == QSTRING_TAG_TYPE_PTR ) {
    *num_parts = 1;
    return arg.ptr.bytes->length;
  } else {
    qbuffer_iter_t cur;
    qbuffer_iter_t end;
    qbytes_t* bytes;
    int64_t skip, len;
    int64_t buffer_space = 0;
    int64_t n_parts = 0;

    cur = qbuffer_begin(arg.buffer.buffer);
    end = qbuffer_end(arg.buffer.buffer);

    while( qbuffer_iter_num_bytes(cur, end) > 0 ) {
      qbuffer_iter_get(cur, end, &bytes, &skip, &len);
      buffer_space += bytes->len;
      qbuffer_iter_next_part( arg.buffer.buffer, &cur );
      n_parts++;
    }

    *num_parts = n_parts;
    return buffer_space;
  }
}

// You must already know that *dst has enough room.
// Does not put a terminating null.
static inline
void qstring_copyto(void* dst, qstring_t arg, int64_t skip, int64_t trunc)
{
  qstring_type_t type = qstring_type(arg.small.tag);
  if( type == QSTRING_TAG_TYPE_SMALL ) {
    int64_t len = qstring_length(arg);
    memcpy( dst, VOID_PTR_ADD(&arg, skip), len - skip - trunk);
  } else if( type == QSTRING_TAG_TYPE_PTR ) {
    memcpy( dst, VOID_PTR_ADD(arg->ptr->bytes->data, skip),
                 arg->ptr->bytes->length - skip - trunc);
  } else {
    qbuffer_iter_t start;
    qbuffer_iter_t end;

    start = qbuffer_begin(arg.buffer.buffer);
    end = qbuffer_end(arg.buffer.buffer);
    qbuffer_iter_advance(arg.buffer.buffer, &start, skip);
    qbuffer_iter_advance(arg.buffer.buffer, &end, -trunc);

    qbuffer_copyout(arg.buffer.buffer, start, end, dst, qbuffer_iter_num_bytes(start, end));
  }
}

err_t qstring_copy(qstring_t* dst, qstring_t arg, int64_t skip, int64_t trunc)
{
  int64_t len = qstring_length(arg);
  int64_t newlen = len - skip - trunc;
  qstring_type_t type = qstring_type(arg.small.tag);
  err_t err;

  if( newlen <= QSTRING_TAG_SMALL_MAXLEN ) {
    if( type == QSTRING_TAG_TYPE_SMALL && len == newlen ) {
      // Just copy the structure.
      dst->words.word1 = arg.words.word1;
      dst->words.word2 = arg.words.word2;
    } else {
      qstring_copyto(dst, arg, skip, trunc);
      dst->small.tag = (arg.small.tag & QSTRING_TAG_NOT_SMALL_LEN_MASK) | (QSTRING_TAG_SMALL_MAXLEN - newlen);
    }
  } else {
    int64_t num_parts;
    int64_t bufspace = qstring_buffer_size(arg, &num_parts);
    if( bufspace - newlen >= QSTRING_TAG_MAX_UNUSED_BUFFER ) {
      // OK, we would waste too much space if we did
      // not copy, so we copy.
      err = qbytes_create_calloc( & dst->ptr.ptr, newlen );
      if( err ) return err;
      qstring_copyto( dst->ptr.ptr->bytes, arg, skip, trunc);
    } else {
      // If 1 thing and it fits, use qbytes
      // else use qbuffer.
    }
    // How much unused 
    // Do we believe we should copy?
    // yes - if there's too much '


    // We can:
    // - create a new qbytes to hold the data
    // - copy-by-immutable-reference into a qbuffer

    // are we copying data ?? ... 
    // Create a qbytes to hold the data.
  }
}


/* Want e.g. repeated appendings to be O(n) not O(n^2).
   Can a string contain write-once qbytes in unsharable range?
   (i believe so).

   -- copy each time is not efficient.
   -- can create new qbuffer/consolidate qbuffers
      logarithmically.

   -- 
