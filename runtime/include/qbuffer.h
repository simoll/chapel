#ifndef _QBUFFER_H_
#define _QBUFFER_H_

#include "sys_basic.h"
#include "chpl-atomics.h"

#include <inttypes.h>
#include <sys/uio.h>
#include <alloca.h>
#include "deque.h"

// We should have gasnett_atomic_t from sys_basic

typedef uint_least64_t qb_refcnt_base_t;
typedef atomic_uint_least64_t qbytes_refcnt_t;

#define DO_INIT_REFCNT(ptr) atomic_init_uint_least64_t (&ptr->ref_cnt, 1)
#define DO_GET_REFCNT(ptr) atomic_load_uint_least64_t (&ptr->ref_cnt)

#define DO_RETAIN(ptr) \
{ \
  /* do nothing to NULL */ \
  if( ptr ) { \
    qb_refcnt_base_t old_cnt = atomic_fetch_add_uint_least64_t (&ptr->ref_cnt, 1); \
    /* if it was 0, we couldn't have had a ref to it */ \
    if( old_cnt == 0 ) *(volatile int *)(0) = 0; /* deliberately segfault. */ \
    /* if it is now 0, we overflowed the number */ \
    if( old_cnt + 1 == 0 ) *(volatile int *)(0) = 0; /* deliberately segfault. */ \
  } \
}

#define DO_RELEASE(ptr, free_function) \
{ \
  /* do nothing to NULL */ \
  if( ptr ) { \
    qb_refcnt_base_t old_cnt = atomic_fetch_sub_uint_least64_t (&ptr->ref_cnt, 1); \
    if( old_cnt == 1 ) { \
      /* that means, after we decremented it, the count is 0. */ \
      free_function(ptr); \
    } else { \
      /* old_cnt == 0 is a fatal error (underflow) */ \
      if( old_cnt == 0 ) *(volatile int *)(0) = 0; /* deliberately segfault. */ \
    } \
  } \
}

#define DO_DESTROY_REFCNT(ptr) atomic_destroy_uint_least64_t (&ptr->ref_cnt)

// how large is an iobuf?
extern size_t qbytes_iobuf_size;
extern size_t qbytes_smallbuf_size;

struct qbytes_s;

// a free function
typedef void (*qbytes_free_t)(struct qbytes_s*);

/* A qbytes_t is just some data with a length.
 * It is a reference-counted class type.
 * Once a qbytes_t is made, only the reference count may change;
 * all the other fields must remain fixed. (Note that the
 * memory pointed to by data may change, but depending on
 * the context, that might be immutable as well).
 *
 * The free function must free both the bytes buffer as well
 * as the qbytes object itself.
 *
 * Multiple threads accessing qbytes must be managed by means
 * outside of the qbytes.
 *
 * It would be possible to store the reference count under
 * a different pointer, so that instead of qbytes_t* we
 * would use {qbytes_t*, refcnt_t*}, but experiments
 * with C++ reference counting implementations indicate
 * that this kind of "internal reference count" is
 * faster than the 2-pointer version.
 */
typedef struct qbytes_s {
  // reference count which is atomically updated
  qbytes_refcnt_t ref_cnt;
  // all of the other fields 
  void* data;
  int64_t len;
  qbytes_free_t free_function;
} qbytes_t;

// These are necessary for extern class in Chapel.
typedef qbytes_t _qbytes_ptr_t;
typedef qbytes_t* qbytes_ptr_t;
#define QBYTES_PTR_NULL NULL

// increment the reference count
static inline
void qbytes_retain(qbytes_t* qb)
{
  DO_RETAIN(qb);
}

// decrement the reference count; free on 0.
static inline
void qbytes_release(qbytes_t* qb)
{
  DO_RELEASE(qb, qb->free_function);
}

// for being called by free functions... frees only the qbytes itself.
void _qbytes_free_qbytes(qbytes_t* b);
// free a NULL one
void qbytes_free_null(qbytes_t* b);
// unmap the data
void qbytes_free_munmap(qbytes_t* b);
// free the data
void qbytes_free_sys_free(qbytes_t* b);
void qbytes_free_qio_free(qbytes_t* b);

void _qbytes_init_generic(qbytes_t* ret, void* give_data, int64_t len, qbytes_free_t free_function);
err_t qbytes_create_generic(qbytes_t** out, void* give_data, int64_t len, qbytes_free_t free_function);
err_t _qbytes_init_iobuf(qbytes_t* ret, int64_t size);
err_t qbytes_create_iobuf(qbytes_t** out);
err_t _qbytes_init_calloc(qbytes_t* ret, int64_t len);
err_t qbytes_create_calloc(qbytes_t** out, int64_t len);
err_t qbytes_create_malloc(qbytes_t** out, int64_t len);

// Create a page-aligned buffer if it's >= qbytes_iobuf_size
// or just a normally allocated buffer otherwise.
err_t qbytes_create_buffer(qbytes_t** out, int64_t len);

static inline
int64_t qbytes_len(qbytes_t* b)
{
  return b->len;
}

static inline
void* qbytes_data(qbytes_t* b)
{
  return b->data;
}

typedef enum {
  QB_PART_FLAGS_NONE = 0,

  // the regions of the qbytes object not used by
  // buffer part could be used and mutated.
  QB_PART_FLAGS_REST_MUTABLE = 1,

  // the data in the buffer part can be mutated
  // (normally that means it has not been shared)
  QB_PART_FLAGS_MUTABLE = 2,
} qbuffer_part_flags_t;

typedef struct qbuffer_part_s {
  // part refers to the region
  // [bytes->data + itemsz*skip, bytes->data + itemsz*(skip + len) )
  qbytes_t* bytes;
  int64_t skip; // in items
  int64_t len; // in items; does not include skip
                      
  // end_offset is in items but betwen buf->offset_start and buf->offset_end
  int64_t end_offset; // in items; subtract len_items from this to get start_offset

  qbuffer_part_flags_t flags;
 
  // for UTF-8 strings. INT64_MIN if not known.
  int64_t end_offset_characters;
} qbuffer_part_t;

typedef enum {
  QB_OTHER = 0,
  QB_EVEN = 1,
  QB_POWERS = 2
} qbuffer_type_t;

/* A buffer is a group of bytes_t objects. It has:
 *  - some number of bytes_t objects (reference counted)
 *
 *  We say a buffer refers to a total of n bytes,
 *  and it does so with b bytes_t objects.
 *
 *  Buffers support O(1) push/pop on front/back of bytes objects,
 *  simple&fast iteration, and O(1) or O(log b) indexing.
 *
 *  Inserting/deleting at any position O(b) - but in practice
 *  depending on the situation it may be O(sqrt(b)) or O(1).
 *
 *  For buffers that grow, we use the structure  
 *  described in "Singly Resizable Arrays and Deques" section of
 *  Brodnik Carlsson Demaine Munro Sedgewick
 *  "Resizable Arrays in Optimal Time and Space" which gives O(1)
 *  indexing and O(sqrt(n)) space overhead with O(sqrt(n)) blocks.
 *  We modify that algorithm to treat the first three blocks differently:
 *   - the optional first block can be a non-power-of-two size
 *   - the second block + the optional first block add to a power of 2,
 *     which is 1 << log2_items_starting
 *   - the third block is the same size as second block + optional first block,
 *     that is, 1 << log2_items_starting
 *
 *  Why?
 *   - non-power-of-2 first block allows a growable array to
 *     start out by referring to a qbytes
 *   - third block same size as second + first causes each block
 *     of size 2^k to be 2^k aligned were the result to be flattened -
 *     which is a useful property for I/O where page alignment might
 *     lead to higher performance.
 *
 *  Note - as implementation terminology, we call a block the "anchor" block:
 *    If there is an optional out-of-pattern first block,
 *    the "anchor" block is the second block, so that end_offset
 *    of the "anchor" block is in pattern. If there is no optional
 *    out-of-pattern first block, the "anchor" block is the first block.
 *
 *  However, one can concatenate buffers or append one buffer to
 *  another. If these are done to a growing "powers" buffer,
 *  the result will not be "powers" (that is, indexing will
 *  become O(log b) ).
 *
 * Buffers are not inherently thread-safe and access should
 * be protected by some other means.
 * 
 * A buffer should be wrapped as a record; the destructor
 * should be called when it goes out of scope.
 */
typedef struct qbuffer_s {
  qbytes_refcnt_t ref_cnt; // atomically updated
  deque_t deque; // contains qbuffer_part_t s 
  int64_t offset_start; // in items
  int64_t offset_end;

  int64_t item_size; // compute indexes in terms of i'th element;
                     // sizes above are in terms of elements (not bytes)!
                     // but in many important cases, element_size == 1.


  // Support 3 different buffer forms:
  //  - "even" all the same block size 2^n, front/back may be empty
  //  - "powers" a la "Resizable Arrays in Optimal Time and Space"
  //  - "other" anything else

  // "even" and "powers" treat the first and second blocks specially.
  qbuffer_type_t type; // QB_OTHER, QB_EVEN, QB_POWERS
  int8_t log2_items_starting; // for "even", == log2_items_per_block
} qbuffer_t;

typedef qbuffer_t _qbuffer_ptr_t;
typedef qbuffer_t* qbuffer_ptr_t;
#define QBUFFER_PTR_NULL NULL

typedef struct qbuffer_iter_s {
  int64_t offset; // valid iter has offset_start <= offset <= offset_end
  deque_iterator_t iter;
} qbuffer_iter_t;

static inline
qbuffer_iter_t qbuffer_iter_null(void) {
  qbuffer_iter_t ret = {0, deque_iterator_null()};
  return ret;
}

void debug_print_qbuffer_iter(qbuffer_iter_t* iter);
void debug_print_qbuffer(qbuffer_t* buf);


static inline
void qbuffer_init_uninitialized(qbuffer_t* buf) {
  deque_init_uninitialized(&buf->deque);
}
static inline
int qbuffer_is_initialized(qbuffer_t* buf) {
  return deque_is_initialized(&buf->deque);
}

/* Initialize a buffer */
err_t qbuffer_init(qbuffer_t* buf);
err_t qbuffer_init_type(qbuffer_t* buf, qbuffer_type_t type);

/* Destroy a buffer inited with qbuffer_init */
err_t qbuffer_destroy_inplace(qbuffer_t* buf);

/* Create a reference-counted buffer ptr */
err_t qbuffer_create(qbuffer_ptr_t* out);
err_t qbuffer_create_type(qbuffer_ptr_t* out, qbuffer_type_t type);

/* Destroy a buffer and free() the pointer;
 * destroys a buffer created with qbuffer_create */
err_t qbuffer_destroy_free(qbuffer_t* buf);


/* Increment a reference count
 */
static inline
void qbuffer_retain(qbuffer_ptr_t buf)
{
  DO_RETAIN(buf);
}

/* Release a reference-counted buffer ptr */
static inline
void qbuffer_release(qbuffer_ptr_t buf)
{
  DO_RELEASE(buf, qbuffer_destroy_free);
}

void qbuffer_extend_back(qbuffer_t* buf);
void qbuffer_extend_front(qbuffer_t* buf);

/* Append a bytes_t to a buffer group.
 * the new buffer part will have the provided flags (specifying mutablility,
 *  can be grown and mutated)
 */
err_t qbuffer_append(qbuffer_t* buf, qbytes_t* bytes, int64_t skip_items, int64_t len_items, qbuffer_part_flags_t flags);

/* Append a buffer to another buffer; the bytes will be shared (reference counts increased)
 * The flags of the original data will be masked with flags_mask
 * */
err_t qbuffer_append_buffer(qbuffer_t* buf, qbuffer_t* src, qbuffer_iter_t src_start, qbuffer_iter_t src_end, qbuffer_part_flags_t flags_mask);

/* Prepend a bytes_t to a buffer group.
 */
err_t qbuffer_prepend(qbuffer_t* buf, qbytes_t* bytes, int64_t skip_items, int64_t len_items, qbuffer_part_flags_t flags);

/* trim functions remove parts that are completely in the area
 * to be removed. */
void qbuffer_trim_front(qbuffer_t* buf, int64_t remove_items);
void qbuffer_trim_back(qbuffer_t* buf, int64_t remove_items);

/* shrink/grow functions make sure you could do O(1) push/pop */
void qbuffer_shrink_back(qbuffer_t* buf, int64_t remove_items);
// Add space on the right of the buffer so that buf->offset_end >= min_end
err_t qbuffer_grow_back(qbuffer_t* buf, int64_t add_items, int round_to_chunk);

/* Remove a part from the front -- disables "powers" */
//err_t qbuffer_pop_front(qbuffer_t* buf);
//err_t qbuffer_pop_back(qbuffer_t* buf); use qbuffer_shrink_back

/* Without changing any memory, changes the offsets
 * used in the buffer (offset_start, offset_end, and offsets in the parts).
 */
void qbuffer_reposition(qbuffer_t* buf, int64_t new_offset_start);

qbuffer_iter_t qbuffer_begin(qbuffer_t* buf);
qbuffer_iter_t qbuffer_end(qbuffer_t* buf);

static inline
ssize_t qbuffer_num_parts(qbuffer_t* buf)
{
  return deque_size(sizeof(qbuffer_part_t), & buf->deque);
}

/* do a and b refer to the same part?
 */
static inline
char qbuffer_iter_same_part(qbuffer_iter_t a, qbuffer_iter_t b) {
  return deque_it_equals(a.iter, b.iter);
}

/* Moves to the beginning of the next part
 */
void qbuffer_iter_next_part(qbuffer_t* buf, qbuffer_iter_t* iter);

/* Moves to the beginning of the previous part
 */
void qbuffer_iter_prev_part(qbuffer_t* buf, qbuffer_iter_t* iter);

/* Move to the beginning of the current part 
 */
void qbuffer_iter_floor_part(qbuffer_t* buf, qbuffer_iter_t* iter);
/* Move to the end of the current part.
 */
void qbuffer_iter_ceil_part(qbuffer_t* buf, qbuffer_iter_t* iter);

/* Advances an iterator using linear search. 
 */
void qbuffer_iter_advance(qbuffer_t* buf, qbuffer_iter_t* iter, int64_t amt);

/* Find offset in window in logarithmic time.
 * Note these offsets start at buf->offset_start, not 0.
 */
qbuffer_iter_t qbuffer_iter_at(qbuffer_t* buf, int64_t offset);

/* How many parts are in an iterator? end >= start
 * always returns 1 + end - start
 */
static inline
ssize_t qbuffer_iter_num_parts(qbuffer_iter_t start, qbuffer_iter_t end)
{
  return 1 + deque_it_difference(sizeof(qbuffer_part_t), end.iter, start.iter);
}

static inline
char qbuffer_iter_equals(qbuffer_iter_t start, qbuffer_iter_t end)
{
  return start.offset == end.offset;
}

/* How many bytes are in an iterator? end >= start
 */
static inline
int64_t qbuffer_iter_num_items(qbuffer_iter_t start, qbuffer_iter_t end)
{
  return end.offset - start.offset;
}

/* How many bytes are after an iterator?
 */
static inline
int64_t qbuffer_iter_num_items_after(qbuffer_t* buf, qbuffer_iter_t iter)
{
  return buf->offset_end - iter.offset;
}

/* How many bytes are before an iterator?
 */
static inline
int64_t qbuffer_iter_num_items_before(qbuffer_t* buf, qbuffer_iter_t iter)
{
  return iter.offset - buf->offset_start;
}

static inline
void _qbuffer_iter_get_items(qbuffer_part_t* qbp, int64_t start_offset, int64_t end_offset, qbytes_t** bytes_out, int64_t* skip_out, int64_t* len_out)
{
  int64_t part_end = qbp->end_offset;
  // these are amounts to add to skip (ie skip is not included)
  int64_t part_start = part_end - qbp->len;
  int64_t start_within = start_offset - part_start;
  int64_t end_within = end_offset - part_start;

  // do not use data before skip
  if( start_within < 0 ) start_within = 0;
  // do not use data after end
  if( end_within > qbp->len ) end_within = qbp->len;

  *bytes_out = qbp->bytes;
  *skip_out = qbp->skip + start_within;
  *len_out = end_within - start_within;
}

// Returns whats in the iterator. If the caller wants to hold on to
// the bytes, it should retain them (this function does not).
// The returned values are in bytes (and not items)
static inline
void qbuffer_iter_get_bytes(qbuffer_t* buf, qbuffer_iter_t iter, qbuffer_iter_t end, qbytes_t** bytes_out, int64_t* skip_bytes_out, int64_t* len_bytes_out)
{
  int64_t skip_items, len_items;
  qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter.iter);
  _qbuffer_iter_get_items(qbp, iter.offset, end.offset, bytes_out, &skip_items, &len_items);
  *skip_bytes_out = buf->item_size * skip_items;
  *len_bytes_out = buf->item_size * len_items;
}

static inline
void qbuffer_iter_get_items(qbuffer_t* buf, qbuffer_iter_t iter, qbuffer_iter_t end, qbytes_t** bytes_out, int64_t* skip_items_out, int64_t* len_items_out)
{
  qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter.iter);
  _qbuffer_iter_get_items(qbp, iter.offset, end.offset, bytes_out, skip_items_out, len_items_out);
}


static inline
int64_t qbuffer_start_offset(qbuffer_t* buf)
{
  return buf->offset_start;
}

static inline
int64_t qbuffer_end_offset(qbuffer_t* buf)
{
  return buf->offset_end;
}

static inline
int64_t qbuffer_len(qbuffer_t* buf)
{
  return buf->offset_end - buf->offset_start;
}

/* Turn a range from a qbuffer into an io-vector. Note that this contains
 * pointers into the qbuffer and is only valid until the qbuffer is changed...
 */
err_t qbuffer_to_iov(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, 
                   size_t max_iov, struct iovec *iov_out, 
                   qbytes_t** bytes_out /* can be NULL */,
                   size_t *iovcnt_out);

/* Returns a single bytes object for the qbuffer.
 * This is like the C++ string.c_str() method;
 *
 * It is the responsibility of the caller to call
 * qbytes_release on the result of this function.
 */
err_t qbuffer_flatten(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, qbytes_t** bytes_out);

/* Create a reference-sharing version of the buffer,
 * starting from current iterator position.
 */
//err_t qbuffer_clone(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, qbuffer_ptr_t* buf_out);

/* Copies bytes from start to end in buffer to ptr.
 * Returns an error if we would exceed ret_len
 * */
err_t qbuffer_copyout(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, void* ptr, size_t ret_len);

/* Copies bytes from ptr to start to end in buffer.
 * Returns an error if we would exceed ret_len
 * */
err_t qbuffer_copyin(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, const void* ptr, size_t ret_len);

err_t qbuffer_copyin_buffer(qbuffer_t* dst, qbuffer_iter_t dst_start, qbuffer_iter_t dst_end,
                            qbuffer_t* src, qbuffer_iter_t src_start, qbuffer_iter_t src_end);

/* Overwrites the qbuffer buffers with a fixed byte.
 * */
err_t qbuffer_memset(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, unsigned char byte);

#define MAX_ON_STACK 128

#ifdef _chplrt_H_

#include "chpl-mem.h"
#define qio_malloc(size) chpl_malloc(size)
#define qio_valloc(size) chpl_valloc(size)
#define qio_calloc(nmemb, size) chpl_calloc(nmemb, size);
#define qio_realloc(ptr, size) chpl_realloc(ptr, size);
#define qio_free(ptr) chpl_free(ptr)

static inline char* qio_strdup(const char* ptr)
{
  char* ret = qio_malloc(strlen(ptr)+1);
  if( ret ) strcpy(ret, ptr);
  return ret;
}

#else

#define qio_malloc(size) malloc(size)
#define qio_valloc(size) valloc(size)
#define qio_calloc(nmemb, size) calloc(nmemb,size)
#define qio_realloc(ptr, size) realloc(ptr, size)
#define qio_free(ptr) free(ptr)
#define sys_free(ptr) free(ptr)
#define qio_strdup(ptr) strdup(ptr)

#endif

#define MAYBE_STACK_ALLOC(size, ptr, onstack) \
{ \
  if( size <= MAX_ON_STACK ) { \
    ptr = alloca(size); \
    onstack = 1; \
  } else { \
    ptr = qio_malloc(size); \
    onstack = 0; \
  } \
}


#define MAYBE_STACK_FREE(ptr, onstack) \
{ \
  if( ! onstack ) { \
    qio_free(ptr); \
  } \
}

#define VOID_PTR_DIFF(a,b) (((intptr_t) (a)) - ((intptr_t) (b)))
#define VOID_PTR_ADD(ptr,amt) ((void*)(((char*) (ptr)) + (amt)))
#define VOID_PTR_ALIGN(ptr,align) (((uintptr_t)ptr) & (align - 1))

#endif

