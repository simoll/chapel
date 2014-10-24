

#ifndef SIMPLE_TEST
#include "chplrt.h"
#define QBUF_EXTRA_CHECKS 0
#else
#define QBUF_EXTRA_CHECKS 1
#endif

#include "qbuffer.h"

#include "sys.h"

#include <limits.h>
#include <sys/mman.h>

#include <assert.h>

#ifdef _chplrt_H_
// we use bit-ops defined here, like chpl_leadz8
#include "chplmath.h"
#define qio_leadz64 chpl_leadz64
#else
#define qio_leadz64(x) (__builtin_clzll((unsigned long long) (x)))
#endif

#define qio_log2_64(x) (63 - qio_leadz64(x))

// an iobuf ought to be page aligned.
//  - tile64 page size is 64kb
//  - glibc malloc uses MMAP for anything over 128kb by default
//  - 64kb blocks... note tile64 page size is 64K
// this really should be a multiple of page size...
// but we can't know page size at compile time
size_t qbytes_iobuf_size = 128*1024;

// what is smallest buffer? should cover overhead of qbuffer
// in space.
size_t qbytes_smallbuf_size = 256;

// prototypes.

err_t _qbytes_create_iobuf_sz(qbytes_t** out, int64_t size);
void qbytes_free_iobuf(qbytes_t* b);
void debug_print_bytes(qbytes_t* b);
void _qbuffer_trim_back(qbuffer_t* buf, int64_t remove_items, int shrinking);

int64_t _qbuffer_get_block(qbuffer_t* buf, int64_t offset, int* block_bits_out);
int _qbuffer_log2_next(int64_t size, int min_log2);

// global, shared pools.

void _qbytes_free_qbytes(qbytes_t* b)
{
  b->data = NULL;
  b->len = 0;
  b->free_function = NULL;
  DO_DESTROY_REFCNT(b);
  qio_free(b);
}

void qbytes_free_null(qbytes_t* b) {
  _qbytes_free_qbytes(b);
}

void qbytes_free_munmap(qbytes_t* b) {
  err_t err;

  /* I don't believe this is required, but 
   * I've heard here and there it might be for NFS...
   *
  rc = msync(b->data, b->len, MS_ASYNC);
  if( rc ) fprintf(stderr, "Warning - in qbytes_free_munmap, msync failed with %i, errno %i\n", rc, errno);
  */

  err = sys_munmap(b->data, b->len);
  assert( !err );

  _qbytes_free_qbytes(b);
}

void qbytes_free_qio_free(qbytes_t* b) {
  qio_free(b->data);
  _qbytes_free_qbytes(b);
}
void qbytes_free_sys_free(qbytes_t* b) {
  // We need to use the system 'free' function here.
  sys_free(b->data);
  _qbytes_free_qbytes(b);
}

void qbytes_free_iobuf(qbytes_t* b) {
  // iobuf is just something to be freed with free()
  qbytes_free_sys_free(b);
}

void debug_print_bytes(qbytes_t* b)
{
  fprintf(stderr, "bytes %p: data=%p len=%lli ref_cnt=%li free_function=%p\n",
          b, b->data, (long long int) b->len, (long int) DO_GET_REFCNT(b),
          b->free_function);
}

void _qbytes_init_generic(qbytes_t* ret, void* give_data, int64_t len, qbytes_free_t free_function)
{
  ret->data = give_data;
  ret->len = len;
  DO_INIT_REFCNT(ret);
  ret->free_function = free_function;
}

err_t qbytes_create_generic(qbytes_t** out, void* give_data, int64_t len, qbytes_free_t free_function)
{
  qbytes_t* ret = NULL;

  ret = qio_malloc(sizeof(qbytes_t));
  if( ! ret ) return ENOMEM;

  _qbytes_init_generic(ret, give_data, len, free_function);

  *out = ret;

  return 0;
}

err_t _qbytes_init_iobuf(qbytes_t* ret, int64_t size)
{
  void* data = NULL;
  
  // allocate 4K-aligned (or page size aligned)
  // multiple of 4K
  data = qio_valloc(size);
  if( !data ) return ENOMEM;
  // We used to use posix_memalign, but that didn't work on an old Mac;
  // also, this should be page-aligned (vs iobuf_size aligned).
  //err_t err = posix_memalign(&data, qbytes_iobuf_size, qbytes_iobuf_size);
  //if( err ) return err;

  _qbytes_init_generic(ret, data, size, qbytes_free_iobuf);

  return 0;
}



err_t _qbytes_create_iobuf_sz(qbytes_t** out, int64_t size)
{
  qbytes_t* ret = NULL;
  err_t err;

  ret = qio_malloc(sizeof(qbytes_t));
  if( ! ret ) return ENOMEM;

  err = _qbytes_init_iobuf(ret, size);
  if( err ) {
    qio_free(ret);
    *out = NULL;
    return err;
  }

  *out = ret;
  return 0;
}
err_t qbytes_create_iobuf(qbytes_t** out)
{
  return _qbytes_create_iobuf_sz(out, qbytes_iobuf_size);
}

err_t qbytes_create_calloc(qbytes_t** out, int64_t len)
{
  qbytes_t* ret = NULL;
  void* data;

  ret = qio_calloc(1, sizeof(qbytes_t) + len);
  if( ! ret ) return ENOMEM;

  data = ret + 1; // ie ret + sizeof(qbytes_t)
  _qbytes_init_generic(ret, data, len, qbytes_free_null);

  *out = ret;
  return 0;
}

err_t qbytes_create_malloc(qbytes_t** out, int64_t len)
{
  qbytes_t* ret = NULL;
  void* data;

  ret = qio_malloc(sizeof(qbytes_t) + len);
  if( ! ret ) return ENOMEM;

  data = ret + 1; // ie ret + sizeof(qbytes_t)
  _qbytes_init_generic(ret, data, len, qbytes_free_null);

  *out = ret;
  return 0;
}


err_t qbytes_create_buffer(qbytes_t** out, int64_t len)
{
  if( len < qbytes_iobuf_size ) {
    return qbytes_create_malloc(out, len);
  } else {
    return _qbytes_create_iobuf_sz(out, len);
  }
}

void debug_print_qbuffer_iter(qbuffer_iter_t* iter)
{
  fprintf(stderr, "offset=%lli ", (long long int) iter->offset);
  debug_print_deque_iter(& iter->iter);
}

void debug_print_qbuffer(qbuffer_t* buf)
{
  deque_iterator_t cur = deque_begin(& buf->deque);
  deque_iterator_t end = deque_end(& buf->deque);

  fprintf(stderr, "buf %p: offset_start=%lli offset_end=%lli deque:\n",
          buf, (long long int) buf->offset_start, (long long int) buf->offset_end);

  // Print out the deque iterators
  debug_print_deque_iter(&cur);
  debug_print_deque_iter(&end);

  while( ! deque_it_equals(cur, end) ) {
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, cur);
    fprintf(stderr, "part %p: bytes=%p (data %p len %lli) skip=%lli len=%lli end=%lli\n", 
            qbp, qbp->bytes, qbp->bytes->data, (long long int) qbp->bytes->len,
            (long long int) qbp->skip,
            (long long int) qbp->len,
            (long long int) qbp->end_offset);

    deque_it_forward_one( sizeof(qbuffer_part_t), &cur );
  }
}

err_t qbuffer_init_type(qbuffer_t* buf, qbuffer_type_t type)
{
  memset(buf, 0, sizeof(qbuffer_t));
  buf->item_size = 1;
  buf->type = type;
  DO_INIT_REFCNT(buf);
  return deque_init(sizeof(qbuffer_part_t), & buf->deque, 0);
  //return 0;
}

err_t qbuffer_init(qbuffer_t* buf)
{
  return qbuffer_init_type(buf, QB_OTHER);
}

err_t qbuffer_destroy_inplace(qbuffer_t* buf)
{
  err_t err = 0;
  deque_iterator_t cur = deque_begin(& buf->deque);
  deque_iterator_t end = deque_end(& buf->deque);

  while( ! deque_it_equals(cur, end) ) {
    qbuffer_part_t* qbp = deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, cur);

    // release the qbuffer.
    qbytes_release(qbp->bytes);

    deque_it_forward_one(sizeof(qbuffer_part_t), &cur);
  }

  // destroy the deque
  deque_destroy(& buf->deque);

  DO_DESTROY_REFCNT(buf);

  return err;
}

err_t qbuffer_create_type(qbuffer_t** out, qbuffer_type_t type)
{
  qbuffer_t* ret = NULL;
  err_t err;

  ret = qio_malloc(sizeof(qbuffer_t));
  if( ! ret ) return ENOMEM;

  err = qbuffer_init_type(ret, type);
  if( err ) {
    qio_free(ret);
    return err;
  }

  *out = ret;

  return 0;
}

err_t qbuffer_create(qbuffer_t** out)
{
  return qbuffer_create_type(out, QB_OTHER);
}

err_t qbuffer_destroy_free(qbuffer_t* buf)
{
  err_t err;
  err = qbuffer_destroy_inplace(buf);
  qio_free(buf);
  return err;
}

// skip, len, end are in items.
static
err_t _qbuffer_init_part(qbuffer_part_t* p, qbytes_t* bytes, int64_t skip, int64_t len, int64_t end_offset, qbuffer_part_flags_t flags, int64_t itemsz)
{
  if( len < 0 || skip < 0 ) return EINVAL;
  if( itemsz*(skip + len) < 0 ) return EINVAL;
  if( itemsz*(skip + len) > bytes->len ) return EINVAL;

  qbytes_retain(bytes);

  p->bytes = bytes;
  p->skip = skip;
  p->len = len;
  p->end_offset = end_offset;
  p->flags = flags;
  p->end_offset_characters = INT64_MIN;

  return 0;
}

// does not change "powers" or "even" method
static
err_t _qbuffer_append_internal(qbuffer_t* buf, qbytes_t* bytes, int64_t skip_items, int64_t len_items, qbuffer_part_flags_t flags)
{
  qbuffer_part_t part;
  int64_t new_end;
  err_t err;

  new_end = buf->offset_end + len_items;
  // init part retains the bytes.
  err = _qbuffer_init_part(&part, bytes, skip_items, len_items, new_end, flags, buf->item_size);
  if( err ) return err;

  err = deque_push_back(sizeof(qbuffer_part_t), &buf->deque, &part);
  if( err ) {
    qbytes_release(bytes); // release the bytes.
    return err;
  }

  // update the buffer's end
  buf->offset_end = new_end;

  return 0;
}

static inline
int _is_powers(qbuffer_t* buf)
{
  return buf->type == QB_POWERS;
}

static inline
int _is_even(qbuffer_t* buf)
{
  return buf->type == QB_EVEN;
}
static inline
int _is_other(qbuffer_t* buf)
{
  return buf->type == QB_OTHER;
}


static inline
void _make_other(qbuffer_t* buf)
{
  buf->type = QB_OTHER;
  buf->log2_items_starting = 0;
}

// returns a block index
static inline
int64_t _powers_get_block(int log2_items_starting, int64_t offset, int* block_bits_out)
{
  // "powers" type
  uint64_t norm_offset;
  int block_bits;
  int log_blocks_per_superblock;
  int superblock;
  int block_in_superblock;
  //uint64_t offset_in_block;
  uint64_t blocks_before_superblock;
  uint64_t one = 1;
  int64_t block_index;
  uint64_t zero_odd_one_even;

  if( QBUF_EXTRA_CHECKS ) assert(offset >= 0);

  // Otherwise, how far do we need to jump ahead?
  norm_offset = offset;
  norm_offset >>= log2_items_starting;
  if( norm_offset > 0 ) {
    superblock = 64 - qio_leadz64(norm_offset);
    block_bits = superblock >> 1; // ie floor(s/2)
    log_blocks_per_superblock = (superblock - 1) >> 1; // ie floor((s-1)/2)
    block_in_superblock = (norm_offset ^ (one << (superblock-1))) >> block_bits;
    //offset_in_block = norm_offset & ( (one << block_bits) - one);
    //
    zero_odd_one_even = (one ^ (superblock & 1));
    blocks_before_superblock =
      (one << (log_blocks_per_superblock + 1)) +
      (zero_odd_one_even << log_blocks_per_superblock) - 1;
    block_index = blocks_before_superblock + block_in_superblock;
  } else {
    block_index = 0;
    block_bits = 0;
    //offset_in_block = 0;
  }

  block_bits += log2_items_starting;

  if( block_bits_out ) *block_bits_out = block_bits;
  return block_index;
}


static inline
int64_t _even_get_block(int log2_items_starting, int64_t offset, int* block_bits_out)
{
  if( block_bits_out ) *block_bits_out = log2_items_starting;
  return offset >> log2_items_starting;
}

int64_t _qbuffer_get_block(qbuffer_t* buf, int64_t offset, int* block_bits_out) {
  if( _is_powers(buf) ) {
    return _powers_get_block(buf->log2_items_starting, offset, block_bits_out);
  }
  if( _is_even(buf) ) {
    return _even_get_block(buf->log2_items_starting, offset, block_bits_out);
  }
  *block_bits_out = 0;
  return 0;
}

// returns log2 such than
// (1 << log2) > 3*size/2
int _qbuffer_log2_next(int64_t size, int min_log2)
{
  int64_t one = 1;
  int log2;

  if( size == 0 ) size = 1;

  log2 = qio_log2_64(size);

  if( (one << log2) < size ) {
    // round up.
    log2++;

    // if e.g. qbp->len = 2^x - 1,
    // we want to grow directly to the
    // next power-of-two without allocating just 1 item.
    if( (one << log2) - size < qbytes_smallbuf_size ) {
      // round up again.
      log2++;
    }
  }

  if( log2 < min_log2 ) log2 = min_log2;

  return log2;
}

static inline
int64_t _blocks_for_size(int64_t item_size, int64_t buf_size)
{
  int64_t blocksz;
  // compute a block size of qbytes_iobuf_size or 1 item
  if( item_size < buf_size ) {
    blocksz = buf_size / item_size;
  } else {
    blocksz = 1;
  }
  return blocksz;
}

// If we were to prepend a block and keep the existing pattern,
// what size would it be?
// Returns false if it would break the pattern (ie first block not full,
// or first block is currently a split block).
// Assumes that extending the existing block is not going to work.
static
int _would_grow_front(qbuffer_t* buf, int64_t *expect_size, int8_t* new_log2_items_starting)
{
  int64_t one = 1;

  *expect_size = 0;
  *new_log2_items_starting = 0;

  if( _is_other(buf) ) {
    return 0;
  }

  if( deque_size(sizeof(qbuffer_part_t), &buf->deque) == 0 ) {
    return 0;
  }

  // if there is only one block and it ends on a power-of-two
  // then we can add a block before it to make the total
  // size a power-of-two
  if( deque_size(sizeof(qbuffer_part_t), &buf->deque) == 1 ) {
    int log2;
    qbuffer_part_t* qbp;
   
    qbp = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, deque_begin(& buf->deque));
    log2 = _qbuffer_log2_next(qbp->len, buf->log2_items_starting);
    // is the end of qbp aligned to log2?
    if( (qbp->end_offset & ((one << log2) - 1)) == 0 ) {
      // OK, then we would round qbp->len to log2,
      // but it might be there already... if it is, fall through
      // to other cases
      if( qbp->len < (one << log2) ) {
        // add a block of size (one << log2) - qbp->len
        *expect_size = (one << log2) - qbp->len;
        *new_log2_items_starting = log2;
        return 1;
      }
    }
  }

  if( _is_powers(buf) || _is_even(buf) ) {
    int64_t first_block;
    int64_t second_block;
    int64_t before_block;
    int block_bits = 0;

    if( _is_powers(buf) ) {
      // We can't continue to negative numbers...
      if( buf->offset_start - 1 <= 0 ) return 0;
    }

    first_block = _qbuffer_get_block(buf,
                                     buf->offset_start,
                                     NULL);

    before_block = _qbuffer_get_block(buf,
                                      buf->offset_start - 1,
                                      &block_bits);

    if( _is_powers(buf) ) {
      // We can't continue to negative numbers...
      if( before_block < 0 ) return 0;
    }

    if( before_block == first_block - 1 ) {
      // also check that second block == first_block + 1,
      // in order to handle the split block.
      { // checked size >= 0 above
        qbuffer_part_t* qbp;
        qbp = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, deque_begin(& buf->deque));

        second_block = _qbuffer_get_block(buf,
                                          qbp->end_offset,
                                          NULL);

        if( second_block == first_block + 1 ) {
          // OK, we can preserve the pattern.
          *expect_size = (one << block_bits);
          *new_log2_items_starting = buf->log2_items_starting;
          return 1;
        }
      }
    }
  }

  return 0;
}

// If we were to append a block and keep the existing pattern,
// what size would it be?
// Returns false if it would break the pattern (ie last block not full)
// Assumes that extending the existing block is not going to work.
static
int _would_grow_back(qbuffer_t* buf, int64_t *expect_size, int8_t *new_log2_items_starting)
{
  int64_t one = 1;

  *expect_size = 0;
  *new_log2_items_starting = 0;

  if( _is_other(buf) ) {
    return 0;
  }

  if( deque_size(sizeof(qbuffer_part_t), &buf->deque) == 0 ) {
    return 0;
  }

  // if there is only one block, and it does not already end
  // on a power-of-two, then we add new anchor block
  // so that the 2nd block ends on new_log2_items_starting.
  if( deque_size(sizeof(qbuffer_part_t), &buf->deque) == 1 ) {
    int log2, log2next;
    int64_t use_len;
    int64_t masked;
   
    if( _is_powers(buf) ) {
      use_len = buf->offset_end;
    } else {
      use_len = buf->offset_end - buf->offset_start;
    }

    log2 = qio_log2_64(use_len);
    if( (one << log2) < use_len ) log2++;
    if( log2 < buf->log2_items_starting ) log2 = buf->log2_items_starting;

    // is the end-offset already aligned with log2?
    if( (buf->offset_end & ((one << log2) - 1)) == 0 ) {
      // OK. We'll handle it below; no need for a split block.
    } else {
      log2next = _qbuffer_log2_next(use_len, buf->log2_items_starting);
      // figure out the new block size so that end_offset will
      // be log2-next-aligned.
      masked = buf->offset_end & ((one << log2next) - 1);
      *expect_size = (one << log2next) - masked;
      *new_log2_items_starting = log2next;
      return 1;
    }
  }

  if( _is_powers(buf) || _is_even(buf) ) {
    int64_t last_block;
    int64_t after_block;
    int block_bits = 0;

    last_block = _qbuffer_get_block(buf,
                                    buf->offset_end - 1,
                                    NULL);
    after_block = _qbuffer_get_block(buf,
                                     buf->offset_end,
                                     &block_bits);

    if( after_block == last_block + 1 ) {
      // OK, we can preserve the pattern.
      *expect_size = (one << block_bits);
      *new_log2_items_starting = buf->log2_items_starting;
      return 1;
    }
  }

  return 0;
}
 
// appends and disables "power" or "even" if needed.
err_t qbuffer_append(qbuffer_t* buf, qbytes_t* bytes, int64_t skip_items, int64_t len_items, qbuffer_part_flags_t flags)
{
  int in_pattern = 0;
  int64_t expect_size_items = 0;
  int64_t expect_size_bytes = 0;
  int8_t new_log2_items_starting = 0;
  err_t err;

  in_pattern = _would_grow_back(buf, &expect_size_items, &new_log2_items_starting);
  if( in_pattern ) {
    expect_size_bytes = buf->item_size * expect_size_items;

    in_pattern = 0;
    // check - is new block mutable and mutable extendable?
    // is the new buffer correctly sized?
    if( (flags & QB_PART_FLAGS_MUTABLE) ) {
      if( (flags & QB_PART_FLAGS_REST_MUTABLE) ) {
        // we need total bytes to be the right size.
        if( expect_size_bytes == bytes->len && skip_items == 0 ) in_pattern = 1;
      } else {
        // we need provided region to be the right size.
        if( expect_size_items == len_items ) in_pattern = 1;
      }
    }
  }

  if( ! in_pattern ) {
    if( deque_size(sizeof(qbuffer_part_t), &buf->deque) == 0 ) {
      // adding 1st block is always OK.
    } else if( ! _is_other(buf) ) {
      // disable "powers" or "even"
      _make_other(buf);
    }
  }

  err = _qbuffer_append_internal(buf, bytes, skip_items, len_items, flags);
  if( err ) return err;

  if( in_pattern ) {
    buf->log2_items_starting = new_log2_items_starting;
  }

  return 0;
}

err_t qbuffer_append_buffer(qbuffer_t* dst, qbuffer_t* src, qbuffer_iter_t src_start, qbuffer_iter_t src_end, qbuffer_part_flags_t flags_mask)
{
  qbuffer_iter_t src_cur = src_start;
  qbytes_t* bytes;
  int64_t skip;
  int64_t len;
  err_t err;

  if( dst == src ) return EINVAL;
  if( dst->item_size != src->item_size ) return EINVAL;

  while( qbuffer_iter_num_items(src_cur, src_end) > 0 ) {
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &src->deque, src_cur.iter);
    _qbuffer_iter_get_items(qbp, src_cur.offset, src->offset_end, &bytes, &skip, &len);

    err = qbuffer_append(dst, bytes, skip, len, qbp->flags & flags_mask);
    if( err ) return err;

    qbuffer_iter_next_part(src, &src_cur);
  }

  return 0;
}

static
err_t _qbuffer_prepend_internal(qbuffer_t* buf, qbytes_t* bytes, int64_t skip_items, int64_t len_items, qbuffer_part_flags_t flags)
{
  qbuffer_part_t part;
  int64_t old_start, new_start;
  err_t err;

  old_start = buf->offset_start;
  new_start = old_start - len_items;

  // init part retains the bytes.
  err = _qbuffer_init_part(&part, bytes, skip_items, len_items, old_start, flags, buf->item_size);
  if( err ) return err;

  err = deque_push_front(sizeof(qbuffer_part_t), &buf->deque, &part);
  if( err ) {
    qbytes_release(bytes); // release the bytes.
    return err;
  }

  buf->offset_start = new_start;

  return 0;
}

err_t qbuffer_prepend(qbuffer_t* buf, qbytes_t* bytes, int64_t skip_items, int64_t len_items, qbuffer_part_flags_t flags)
{
  int in_pattern = 0;
  int64_t expect_size_items = 0;
  int64_t expect_size_bytes = 0;
  int8_t new_log2_items_starting = 0;
  err_t err;

  in_pattern = _would_grow_front(buf, &expect_size_items, &new_log2_items_starting);
  if( in_pattern ) {
    expect_size_bytes = buf->item_size * expect_size_items;

    in_pattern = 0;
    // check - is new block mutable and mutable extendable?
    // is the new buffer correctly sized?
    if( (flags & QB_PART_FLAGS_MUTABLE) ) {
      if( (flags & QB_PART_FLAGS_REST_MUTABLE) ) {
        int64_t end_within = skip_items + len_items;
        // we need total bytes to be the right size.
        if( expect_size_bytes == bytes->len &&
            end_within == expect_size_items ) in_pattern = 1;
      } else {
        // we need provided region to be the right size.
        if( expect_size_items == len_items ) in_pattern = 1;
      }
    }
  }

  if( ! in_pattern ) {
    if( deque_size(sizeof(qbuffer_part_t), &buf->deque) == 0 ) {
      // adding 1st block is always OK.
    } else if( ! _is_other(buf) ) {
      // disable "powers" or "even"
      _make_other(buf);
    }
  }

  err = _qbuffer_prepend_internal(buf, bytes, skip_items, len_items, flags);
  if( err ) return err;

  if( in_pattern ) {
    buf->log2_items_starting = new_log2_items_starting;
  }

  return 0;
}

// Adds *mutable* space to the right side of the buffer until
// buf->offset_end >= new_end
// then set the end of the buffer to be new_end unless round_to_chunk is passed.
// Buffers added by this function are marked mutable.
err_t qbuffer_grow_back(qbuffer_t* buf, int64_t add_items, int round_to_chunk)
{
  err_t err = 0;
  int64_t new_end = buf->offset_end + add_items;
  int64_t was_end = buf->offset_end;

  // Do nothing if growing unnecessary.
  if( new_end < buf->offset_end ) return 0;

  // Can we extend space on the right? Do try.
  if( deque_size(sizeof(qbuffer_part_t), &buf->deque) > 0 ) {
    // Get the last part.
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, deque_last(sizeof(qbuffer_part_t), &buf->deque));

    if( (qbp->flags & QB_PART_FLAGS_REST_MUTABLE) &&
        buf->item_size * (qbp->skip + qbp->len) < qbp->bytes->len ) {
      int64_t bytes_items = qbp->bytes->len / buf->item_size;
      int64_t add = bytes_items - qbp->skip - qbp->len;
      qbp->end_offset += add;
      qbp->len += add;
      buf->offset_end = qbp->end_offset;
    }
  }

  // Add blocks to our buffer
  while( new_end > buf->offset_end ) {
    qbytes_t* bytes = NULL;
    int64_t blocksz = -1;
    int8_t new_log2_items_starting = 0;
    _would_grow_back(buf, &blocksz, &new_log2_items_starting);

    if( blocksz <= 0 ) {
      int64_t buf_sz = qbytes_iobuf_size;
      if( _is_powers(buf) ) {
        buf_sz = qbytes_smallbuf_size; 
      }
      blocksz = _blocks_for_size(buf->item_size, buf_sz);
      new_log2_items_starting = qio_log2_64(blocksz);
    }

    err = qbytes_create_buffer(&bytes, buf->item_size * blocksz);
    if( err ) goto error;
    err = qbuffer_append(buf, bytes, 0, blocksz, QB_PART_FLAGS_REST_MUTABLE|QB_PART_FLAGS_MUTABLE);
    qbytes_release(bytes);
    if( err ) goto error;
  }

  // Handle trimming back from entire chunk.
  if( round_to_chunk ) {
    // If we're rounding to the entire qbytes,
    // we already did that, do nothing.
  } else {
    // Trim buf->offset_end and lastqbp so they do not exceed new_end.
    if( deque_size(sizeof(qbuffer_part_t), &buf->deque) > 0 ) {
      qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, deque_last(sizeof(qbuffer_part_t), &buf->deque));
      int64_t remove_here = qbp->end_offset - new_end;
      assert( qbp->end_offset >= was_end ); // we must not have shrunk!
      assert( buf->offset_end >= was_end );
      assert( buf->offset_end >= new_end );
      qbp->len -= remove_here;
      qbp->end_offset -= remove_here;
      buf->offset_end = new_end;
    }
  }

error:
  return err;
}

// Removes entire blocks from the right side of the buffer
// to get the minimum buf->offset_end > new_end
// Note if you want the buffer to have a specific number of
// blocks afterwards, use qbuffer_trim_back; this one may
// leave an empty data block at the end.
void qbuffer_shrink_back(qbuffer_t* buf, int64_t remove_items)
{
  // Do nothing if shrinking unnecessary.
  if( remove_items <= 0 ) return;
  _qbuffer_trim_back(buf, remove_items, 1);
}


static inline
void _qbuffer_setflags_truncate(qbuffer_part_t* qbp)
{
  // if it's not mutable, once we truncate it
  // the unused portion will not be mutable either.
  if( ! (qbp->flags & QB_PART_FLAGS_MUTABLE) ) {
    if( qbp->flags & QB_PART_FLAGS_REST_MUTABLE ) {
      qbp->flags ^= QB_PART_FLAGS_REST_MUTABLE;
    }
  }
}

void qbuffer_trim_front(qbuffer_t* buf, int64_t remove_items)
{
  int64_t new_start = buf->offset_start + remove_items;

  if( remove_items == 0 ) return;
  
  assert( remove_items > 0 );
  assert( new_start <= buf->offset_end );

  while( deque_size(sizeof(qbuffer_part_t), &buf->deque) > 0 ) {
    // Get the first part.
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, deque_begin(& buf->deque));

    if( qbp->end_offset - qbp->len < new_start ) {
      // we might remove it entirely, or maybe
      // we just adjust its length and skip.
      if( qbp->end_offset <= new_start ) {
        qbytes_t* bytes = qbp->bytes;
        // ends entirely before new_start, remove the chunk.
        // Remove it from the deque
        deque_pop_front(sizeof(qbuffer_part_t), &buf->deque);
        // release the bytes.
        qbytes_release(bytes);
      } else {
        // Keep only a part of this chunk.
        int64_t remove_here = new_start - (qbp->end_offset - qbp->len);
        qbp->skip += remove_here;
        qbp->len -= remove_here;
        _qbuffer_setflags_truncate(qbp);
        break; // this is the last one.
      }
    } else {
      break; // we're past
    }
  }

  // Now set the new offset.
  buf->offset_start = new_start;
}


void _qbuffer_trim_back(qbuffer_t* buf, int64_t remove_items, int shrinking)
{
  int64_t new_end = buf->offset_end - remove_items;
  int remove;
  deque_iterator_t cur;

  if( remove_items == 0 ) return;
  assert( remove_items > 0 );
  assert( new_end >= buf->offset_start );

  // Go through the deque removing entire parts.
  while( deque_size(sizeof(qbuffer_part_t), &buf->deque) > 0 ) {
    // Get the last part.
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, deque_last(sizeof(qbuffer_part_t), &buf->deque));

    // In this first loop, we only remove entire qbp at a time.
    if( qbp->end_offset - qbp->len < new_end ) break;

    remove = 1;
    if( shrinking ) {
      remove = 0;
      // only remove it if there is another empty data block at the end.
      if( deque_size(sizeof(qbuffer_part_t), &buf->deque) >= 2 ) {
        deque_iterator_t penultimate;
        qbuffer_part_t* other;
        penultimate = deque_last(sizeof(qbuffer_part_t), &buf->deque);
        deque_it_back_one(sizeof(qbuffer_part_t), &penultimate);
        other = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, penultimate);
        // is other empty (or will be after this operation)?
        if( other->end_offset - other->len >= new_end ) {
          remove = 1;
        } 
      }
      // if we choose not to remove it, exit the loop.
      if( ! remove ) break;
    }
    if( remove ) {
      qbytes_t* bytes = qbp->bytes;
      // starts entirely after new_end, remove the chunk.
      // Remove it from the deque
      deque_pop_back(sizeof(qbuffer_part_t), &buf->deque);
      // release the bytes.
      qbytes_release(bytes);
    }
  }

  // now we will go through the buffer parts backwards looking
  // to truncate existing buffers.
  
  // if there's nothing to fix, do nothing.
  if( deque_size(sizeof(qbuffer_part_t), &buf->deque) == 0 ) return;
  cur = deque_last(sizeof(qbuffer_part_t), &buf->deque);

  while( 1 ) {
    // consider removing cur.
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr( sizeof(qbuffer_part_t), &buf->deque, cur);

    if( qbp->end_offset < new_end ) {
      // Keep only a part of this chunk.
      int64_t remove_here = qbp->end_offset - new_end;
      if( remove_here > qbp->len ) remove_here = qbp->len;
      qbp->len -= remove_here;
      qbp->end_offset -= remove_here;
      _qbuffer_setflags_truncate(qbp);
    } else {
      // we don't need to fix any more buffer parts.
      break;
    }

    // if we're at the start, we're done
    if ( deque_it_equals(cur, deque_begin(&buf->deque) ) ) break;

    // go back one.
    deque_it_back_one(sizeof(qbuffer_part_t), &cur);
  }

  // Now set the new offset.
  buf->offset_end = new_end;
}
void qbuffer_trim_back(qbuffer_t* buf, int64_t remove_items)
{
  _qbuffer_trim_back(buf, remove_items, 0);
}

/*
err_t qbuffer_pop_front(qbuffer_t* buf)
{
  qbytes_t* bytes;
  int64_t skip;
  int64_t len;
  qbuffer_iter_t chunk;

  if ( qbuffer_num_parts(buf) == 0 ) return EINVAL;

  chunk = qbuffer_begin(buf);

  qbuffer_iter_get_items(buf, chunk, qbuffer_end(buf), &bytes, &skip, &len);

  deque_pop_front(sizeof(qbuffer_part_t), &buf->deque);

  buf->offset_start += len;

  // if "powers" method, disable it
  // if "even" method, we're OK.
  if( buf->log2_blocks_per_superblock >= 0 ) {
    // disable "powers"
    buf->log2_blocks_per_superblock = -1;
    buf->log2_items_per_block = -1;
    buf->log2_items_starting = -1;
    buf->has_split_first_block = 0;
  }
 
  return 0;
}
*/

/*
err_t qbuffer_pop_back(qbuffer_t* buf)
{
  qbytes_t* bytes;
  int64_t skip;
  int64_t len;
  qbuffer_iter_t chunk;

  if ( qbuffer_num_parts(buf) == 0 ) return EINVAL;
  
  chunk = qbuffer_end(buf);
  qbuffer_iter_prev_part(buf, &chunk);

  qbuffer_iter_get_items(buf, chunk, qbuffer_end(buf), &bytes, &skip, &len);

  deque_pop_back(sizeof(qbuffer_part_t), &buf->deque);

  buf->offset_end -= len;

  // "powers" and "even" require no special handling.
  return 0;
}
*/

void qbuffer_reposition(qbuffer_t* buf, int64_t new_offset_start)
{
  deque_iterator_t start = deque_begin(& buf->deque);
  deque_iterator_t end = deque_end(& buf->deque);
  deque_iterator_t iter;
  qbuffer_part_t* qbp;
  int64_t diff;

  diff = new_offset_start - buf->offset_start;
  buf->offset_start += diff;
  buf->offset_end += diff;

  iter = start;

  while( ! deque_it_equals(iter, end) ) {
    qbp = deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter);
    qbp->end_offset += diff;
  }
}

qbuffer_iter_t qbuffer_begin(qbuffer_t* buf)
{
  qbuffer_iter_t ret;
  ret.offset = buf->offset_start;
  ret.iter = deque_begin(& buf->deque);
  return ret;
}

qbuffer_iter_t qbuffer_end(qbuffer_t* buf)
{
  qbuffer_iter_t ret;
  ret.offset = buf->offset_end;
  ret.iter = deque_end( & buf->deque );
  return ret;
}

void qbuffer_iter_next_part(qbuffer_t* buf, qbuffer_iter_t* iter)
{
  deque_iterator_t d_end = deque_end( & buf->deque );

  deque_it_forward_one(sizeof(qbuffer_part_t), & iter->iter);

  if( deque_it_equals(iter->iter, d_end) ) {
    // if we're not at the end now... offset is from buf
    iter->offset = buf->offset_end;
  } else {
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter->iter);
    iter->offset = qbp->end_offset - qbp->len;
  }
}

void qbuffer_iter_prev_part(qbuffer_t* buf, qbuffer_iter_t* iter)
{
  qbuffer_part_t* qbp;

  deque_it_back_one(sizeof(qbuffer_part_t), & iter->iter);

  qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter->iter);
  iter->offset = qbp->end_offset - qbp->len;
}

void qbuffer_iter_floor_part(qbuffer_t* buf, qbuffer_iter_t* iter)
{
  deque_iterator_t d_start = deque_begin( & buf->deque );
  deque_iterator_t d_end = deque_end( & buf->deque );

  if( deque_it_equals(iter->iter, d_end) ) {
    if( deque_it_equals(iter->iter, d_start) ) {
      // We're at the beginning. Do nothing.
      return;
    }

    // If we're at the end, just go back one.
    deque_it_back_one(sizeof(qbuffer_part_t), & iter->iter);
  }

  {
    // Now, just set the offset appropriately.
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter->iter);
    iter->offset = qbp->end_offset - qbp->len;
  }
}


void qbuffer_iter_ceil_part(qbuffer_t* buf, qbuffer_iter_t* iter)
{
  deque_iterator_t d_end = deque_end( & buf->deque );

  if( deque_it_equals(iter->iter, d_end) ) {
    // We're at the end. Do nothing.
  } else {
    qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter->iter);
    iter->offset = qbp->end_offset;
    deque_it_forward_one(sizeof(qbuffer_part_t), & iter->iter);
  }
}


/* Advances an iterator using linear search. 
 */
void qbuffer_iter_advance(qbuffer_t* buf, qbuffer_iter_t* iter, int64_t amt)
{
  deque_iterator_t d_begin = deque_begin( & buf->deque );
  deque_iterator_t d_end = deque_end( & buf->deque );

  if( amt >= 0 ) {
    // forward search.
    iter->offset += amt;
    while( ! deque_it_equals(iter->iter, d_end) ) {
      qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter->iter);
      if( iter->offset < qbp->end_offset ) {
        // it's in this one.
        return;
      }
      deque_it_forward_one(sizeof(qbuffer_part_t), & iter->iter);
    }
  } else {
    // backward search.
    iter->offset += amt; // amt is negative

    if( ! deque_it_equals( iter->iter, d_end ) ) {
      // is it within the current buffer?
      qbuffer_part_t* qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter->iter);
      if( iter->offset >= qbp->end_offset - qbp->len ) {
        // it's in this one.
        return;
      }
    }

    // now we have a valid deque element.
    do {
      qbuffer_part_t* qbp;

      deque_it_back_one(sizeof(qbuffer_part_t), & iter->iter);

      qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter->iter);
      if( iter->offset >= qbp->end_offset - qbp->len ) {
        // it's in this one.
        return;
      }
    } while( ! deque_it_equals(iter->iter, d_begin) );
  }
}



// find buffer iterator part in logarithmic time
// finds an offset in the window [offset_start,offset_end]
// (in other words, offset might not start at 0)
// offset is an item index.
qbuffer_iter_t qbuffer_iter_at(qbuffer_t* buf, int64_t offset)
{
  qbuffer_iter_t ret;
  ssize_t num_parts = deque_size(sizeof(qbuffer_part_t), & buf->deque);

  // do some bounds checking to start with
  if( offset < buf->offset_start ) {
    ret.offset = buf->offset_start;
    ret.iter = deque_begin( & buf->deque );
    return ret;
  }
  if( offset >= buf->offset_end || num_parts == 0 ) {
    ret.offset = buf->offset_end;
    ret.iter = deque_end( & buf->deque );
    return ret;
  }

  // from now on, we assume num_parts > 0
  if( _is_powers(buf) || _is_even(buf) ) {
    // "powers" or "even" type; check first block (which may be 'split')
    deque_iterator_t first = deque_begin(& buf->deque);
    deque_iterator_t anchor = first;
    qbuffer_part_t* qbp;
    int64_t one = 1;
    int64_t anchor_end = (one << buf->log2_items_starting);

    // check if it's in the first two blocks.

    // there may be an out-of-pattern first block.
    qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, first);
    if( offset < qbp->end_offset ) {
      // OK. return first == deque_begin.
      ret.offset = offset;
      ret.iter = first;
      return ret;
    }

    // is the end_offset of the first block in the right place?
    // if not, the end_offset of the second block should be,
    // and the 2nd block is the anchor block.

    if( (qbp->end_offset & (anchor_end-1)) != 0 ) {
      // Try the 2nd block
      deque_it_forward_one(sizeof(qbuffer_part_t), &anchor);
      if( QBUF_EXTRA_CHECKS ) {
        assert(num_parts >= 2);
      }
      qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, anchor);
      if( offset < qbp->end_offset ) {
        // OK, it's in the 2nd block.
        ret.offset = offset;
        ret.iter = anchor;
        return ret;
      }
    }

    {
      // powers and even types compute a block index...
      uint64_t block_index;
      deque_iterator_t cur;
      int64_t anchor_inside;
      int64_t anchor_block_index;
      int64_t offset_block_index;

      qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, anchor);

      anchor_inside = qbp->end_offset - 1;
      if( QBUF_EXTRA_CHECKS ) {
        if( _is_powers(buf) ) assert(anchor_inside >= 0);
      }

      anchor_block_index = _qbuffer_get_block(buf, anchor_inside, NULL);
      offset_block_index = _qbuffer_get_block(buf, offset, NULL);
      if( QBUF_EXTRA_CHECKS ) {
        assert( anchor_block_index <= offset_block_index);
      }

      block_index = offset_block_index - anchor_block_index;

      // now use the block index 
      cur = anchor;
      deque_it_forward_n(sizeof(qbuffer_part_t), &cur, block_index);
      ret.offset = offset;
      ret.iter = cur;

      if( QBUF_EXTRA_CHECKS ) {
        // check that the offset is in cur's qbp
        qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, cur);
        assert( offset < qbp->end_offset );
        assert( offset >= qbp->end_offset - qbp->len );
      }
      return ret;
    }
  }

  // If we get here, we need to do binary search.
  // "other" type - do binary search.
  {
    deque_iterator_t first = deque_begin(& buf->deque);
    deque_iterator_t middle;
    qbuffer_part_t* qbp;
    ssize_t half;

    do {
      half = num_parts >> 1;
      middle = first;

      deque_it_forward_n(sizeof(qbuffer_part_t), &middle, half);

      qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, middle);
      if( offset < qbp->end_offset ) {
        num_parts = half;
      } else {
        first = middle;
        deque_it_forward_one(sizeof(qbuffer_part_t), &first);
        num_parts = num_parts - half - 1;
      }
    } while( num_parts > 0 );

    if( deque_it_equals(first, deque_end( & buf->deque )) ) {
      ret = qbuffer_end(buf);
    } else {
      ret.offset = offset;
      ret.iter = first;

      if( QBUF_EXTRA_CHECKS ) {
        // check that the offset is in first's qbp
        qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, first);
        assert( offset < qbp->end_offset );
        assert( offset >= qbp->end_offset - qbp->len );
      }
    }

    return ret;
  }
}

static inline
err_t _qbuffer_to_iov(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, 
                      size_t max_iov, struct iovec *iov_out, 
                      qbytes_t** bytes_out /* can be NULL */,
                      size_t *iovcnt_out,
                      const int64_t item_size)
{
  deque_iterator_t d_end = deque_end(& buf->deque);
  deque_iterator_t iter;
  qbuffer_part_t* qbp;
  size_t i = 0;

  iter = start.iter;

  // invalid range!
  if( start.offset > end.offset ) {
    *iovcnt_out = 0;
    return EINVAL;
  }

  if( deque_it_equals(iter, d_end) ) {
    // start is actually pointing to the end of the deque. no data.
    *iovcnt_out = 0;
    return 0;
  }

  if( deque_it_equals(iter, end.iter) ) {
    // we're only pointing to a single block.
    qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter);
    if( i >= max_iov ) goto error_nospace;
    iov_out[i].iov_base = PTR_ADDBYTES(qbp->bytes->data, item_size * (qbp->skip + (start.offset - (qbp->end_offset - qbp->len))));
    iov_out[i].iov_len = item_size * (end.offset - start.offset);
    if( bytes_out ) bytes_out[i] = qbp->bytes;
    if( iov_out[i].iov_len > 0 ) i++;
  } else {
    // otherwise, there's a possibly partial block in start.
    qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter);
    if( i >= max_iov ) goto error_nospace;
    iov_out[i].iov_base = PTR_ADDBYTES(qbp->bytes->data, item_size * (qbp->skip + (start.offset - (qbp->end_offset - qbp->len))));
    iov_out[i].iov_len = item_size * (qbp->end_offset - start.offset);
    if( bytes_out ) bytes_out[i] = qbp->bytes;
    // store it if we had any data there.
    if( iov_out[i].iov_len > 0 ) i++;


    // Now, on to the next.
    deque_it_forward_one(sizeof(qbuffer_part_t), &iter);

    // until we get to the same block as end, we need to store full blocks.
    while( ! deque_it_equals( iter, end.iter ) ) {
      if( deque_it_equals( iter, d_end ) ) {
        // error: end is not in deque.
        *iovcnt_out = 0;
        return EINVAL;
      }

      qbp = (qbuffer_part_t*) deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter);
      if( i >= max_iov ) goto error_nospace;
      iov_out[i].iov_base = PTR_ADDBYTES(qbp->bytes->data, item_size * qbp->skip);
      iov_out[i].iov_len = item_size * qbp->len;
      if( bytes_out ) bytes_out[i] = qbp->bytes;
      // store it if we had any data there.
      if( iov_out[i].iov_len > 0 ) i++;

      // Now, on to the next.
      deque_it_forward_one(sizeof(qbuffer_part_t), &iter);
    }

    // at the end of the loop
    // is there any data in end?
    if( deque_it_equals(iter, d_end) ) {
      // we're currently pointing to the end; no need to add more.
    } else {
      qbp = deque_it_get_cur_ptr(sizeof(qbuffer_part_t), &buf->deque, iter);
      // add a partial end block. We know it's different from
      // start since we handled that above.
      if( i >= max_iov ) goto error_nospace;
      iov_out[i].iov_base = PTR_ADDBYTES(qbp->bytes->data, item_size * qbp->skip);
      iov_out[i].iov_len = item_size * (end.offset - (qbp->end_offset - qbp->len));
      if( bytes_out ) bytes_out[i] = qbp->bytes;
      if( iov_out[i].iov_len > 0 ) i++;
    }
  }

  *iovcnt_out = i;
  return 0;

error_nospace:
  *iovcnt_out = 0;
  return EMSGSIZE; // EOVERFLOW or ENOBUFS would make sense too
}

err_t qbuffer_to_iov(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, 
                      size_t max_iov, struct iovec *iov_out, 
                      qbytes_t** bytes_out /* can be NULL */,
                      size_t *iovcnt_out)
{
  if( buf->item_size == 1 ) {
    return _qbuffer_to_iov(buf, start, end, max_iov, iov_out, bytes_out, iovcnt_out, 1);
  } else {
    return _qbuffer_to_iov(buf, start, end, max_iov, iov_out, bytes_out, iovcnt_out, buf->item_size);
  }
}

err_t qbuffer_flatten(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, qbytes_t** bytes_out)
{
  int64_t num_items = qbuffer_iter_num_items(start, end);
  ssize_t num_parts = qbuffer_iter_num_parts(start, end);
  struct iovec* iov = NULL;
  size_t iovcnt;
  size_t i,j;
  qbytes_t* ret = NULL;
  int iov_onstack;
  err_t err;
 
  if( num_items < 0 || num_parts < 0 || start.offset < buf->offset_start || end.offset > buf->offset_end ) return EINVAL;

  err = qbytes_create_buffer(&ret, buf->item_size * num_items);
  if( err ) return err;

  MAYBE_STACK_ALLOC(num_parts*sizeof(struct iovec), iov, iov_onstack);
  if( ! iov ) {
    qbytes_release(ret);
    return ENOMEM;
  }

  err = qbuffer_to_iov(buf, start, end, num_parts, iov, NULL, &iovcnt);
  if( err ) {
    MAYBE_STACK_FREE(iov, iov_onstack);
    qbytes_release(ret);
    return err;
  }

  j = 0;
  for( i = 0; i < iovcnt; i++ ) {
    memcpy(PTR_ADDBYTES(ret->data, j), iov[i].iov_base, iov[i].iov_len);
    j += iov[i].iov_len;
  }

  MAYBE_STACK_FREE(iov, iov_onstack);

  *bytes_out = ret;
  return 0;
}

/*
err_t qbuffer_clone(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, qbuffer_ptr_t* buf_out)
{
  int64_t num_bytes = qbuffer_iter_num_bytes(start, end);
  ssize_t num_parts = qbuffer_iter_num_parts(start, end);
  qbytes_t** bytes = NULL;
  struct iovec* iov = NULL;
  size_t iovcnt;
  size_t i;
  int iov_onstack;
  int bytes_onstack;
  err_t err;
  qbuffer_ptr_t ret = NULL;
 
  if( num_bytes < 0 || num_parts < 0 || start.offset < buf->offset_start || end.offset > buf->offset_end ) return EINVAL;

  err = qbuffer_create(&ret);
  if( err ) return err;

  MAYBE_STACK_ALLOC(num_parts*sizeof(struct iovec), iov, iov_onstack);
  MAYBE_STACK_ALLOC(num_parts*sizeof(qbytes_t*), bytes, bytes_onstack);
  if( ! iov || ! bytes ) {
    err = ENOMEM;
    goto error;
  }

  err = qbuffer_to_iov(buf, start, end, num_parts, iov, bytes, &iovcnt);
  if( err ) goto error;

  // now append them all to our present buffer.
  for( i = 0; i < iovcnt; i++ ) {
    int64_t skip = PTR_DIFFBYTES(iov[i].iov_base, bytes[i]->data);
    int64_t len = iov[i].iov_len;

    if( skip < 0 || skip + len > bytes[i]->len ) {
      err = EINVAL;
      goto error;
    }

    qbuffer_append(ret, bytes[i], skip, len);
  }

  MAYBE_STACK_FREE(iov, iov_onstack);
  MAYBE_STACK_FREE(bytes, bytes_onstack);

  *buf_out = ret;
  return 0;

error:
  MAYBE_STACK_FREE(iov, iov_onstack);
  MAYBE_STACK_FREE(bytes, bytes_onstack);
  qbuffer_destroy(ret);
  return err;
}
*/

err_t qbuffer_copyout(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, void* ptr, size_t ret_len)
{
  int64_t num_items = qbuffer_iter_num_items(start, end);
  ssize_t num_parts = qbuffer_iter_num_parts(start, end);
  struct iovec* iov = NULL;
  size_t iovcnt;
  size_t i,j;
  int iov_onstack;
  err_t err;
 
  if( num_items < 0 || num_parts < 0 || start.offset < buf->offset_start || end.offset > buf->offset_end ) return EINVAL;

  MAYBE_STACK_ALLOC(num_parts*sizeof(struct iovec), iov, iov_onstack);
  if( ! iov ) return ENOMEM;

  err = qbuffer_to_iov(buf, start, end, num_parts, iov, NULL, &iovcnt);
  if( err ) goto error;

  j = 0;
  for( i = 0; i < iovcnt; i++ ) {
    if( j + iov[i].iov_len > ret_len ) goto error_nospace;
    memcpy(PTR_ADDBYTES(ptr, j), iov[i].iov_base, iov[i].iov_len);
    j += iov[i].iov_len;
  }

  MAYBE_STACK_FREE(iov, iov_onstack);
  return 0;

error_nospace:
  err = EMSGSIZE;
error:
  MAYBE_STACK_FREE(iov, iov_onstack);
  return err;
}

err_t qbuffer_copyin(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, const void* ptr, size_t ret_len)
{
  int64_t num_items = qbuffer_iter_num_items(start, end);
  ssize_t num_parts = qbuffer_iter_num_parts(start, end);
  struct iovec* iov = NULL;
  size_t iovcnt;
  size_t i,j;
  int iov_onstack;
  err_t err;
 
  if( num_items < 0 || num_parts < 0 || start.offset < buf->offset_start || end.offset > buf->offset_end ) return EINVAL;

  MAYBE_STACK_ALLOC(num_parts*sizeof(struct iovec), iov, iov_onstack);
  if( ! iov ) return ENOMEM;

  err = qbuffer_to_iov(buf, start, end, num_parts, iov, NULL, &iovcnt);
  if( err ) goto error;

  j = 0;
  for( i = 0; i < iovcnt; i++ ) {
    if( j + iov[i].iov_len > ret_len ) goto error_nospace;
    memcpy(iov[i].iov_base, PTR_ADDBYTES(ptr, j), iov[i].iov_len);
    j += iov[i].iov_len;
  }

  MAYBE_STACK_FREE(iov, iov_onstack);
  return 0;

error_nospace:
  err = EMSGSIZE;
error:
  MAYBE_STACK_FREE(iov, iov_onstack);
  return err;
}

err_t qbuffer_copyin_buffer(qbuffer_t* dst, qbuffer_iter_t dst_start, qbuffer_iter_t dst_end,
                            qbuffer_t* src, qbuffer_iter_t src_start, qbuffer_iter_t src_end)
{
  int64_t dst_num_items = qbuffer_iter_num_items(dst_start, dst_end);
  ssize_t dst_num_parts = qbuffer_iter_num_parts(dst_start, dst_end);
  int64_t src_num_items = qbuffer_iter_num_items(src_start, src_end);
  ssize_t src_num_parts = qbuffer_iter_num_parts(src_start, src_end);
  struct iovec* iov = NULL;
  size_t iovcnt;
  size_t i;
  int iov_onstack;
  err_t err;
  qbuffer_iter_t dst_cur, dst_cur_end;
 
  if( dst == src ) return EINVAL;
  if( dst_num_items < 0 || dst_num_parts < 0 || dst_start.offset < dst->offset_start || dst_end.offset > dst->offset_end ) return EINVAL;
  if( src_num_items < 0 || src_num_parts < 0 || src_start.offset < src->offset_start || src_end.offset > src->offset_end ) return EINVAL;
  if( dst->item_size != src->item_size ) return EINVAL;

  MAYBE_STACK_ALLOC(src_num_parts*sizeof(struct iovec), iov, iov_onstack);
  if( ! iov ) return ENOMEM;

  err = qbuffer_to_iov(src, src_start, src_end, src_num_parts, iov, NULL, &iovcnt);
  if( err ) goto error;

  dst_cur = dst_start;
  for( i = 0; i < iovcnt; i++ ) {
    dst_cur_end = dst_cur;
    qbuffer_iter_advance(dst, &dst_cur_end, iov[i].iov_len / dst->item_size);
    err = qbuffer_copyin(dst, dst_cur, dst_cur_end, iov[i].iov_base, iov[i].iov_len);
    if( err ) goto error;
    dst_cur = dst_cur_end;
  }

  MAYBE_STACK_FREE(iov, iov_onstack);
  return 0;

error:
  MAYBE_STACK_FREE(iov, iov_onstack);
  return err;
}

err_t qbuffer_memset(qbuffer_t* buf, qbuffer_iter_t start, qbuffer_iter_t end, unsigned char byte)
{
  int64_t num_items = qbuffer_iter_num_items(start, end);
  ssize_t num_parts = qbuffer_iter_num_parts(start, end);
  struct iovec* iov = NULL;
  size_t iovcnt;
  size_t i;
  int iov_onstack;
  err_t err;
 
  if( num_items < 0 || num_parts < 0 || start.offset < buf->offset_start || end.offset > buf->offset_end ) return EINVAL;

  MAYBE_STACK_ALLOC(num_parts*sizeof(struct iovec), iov, iov_onstack);
  if( ! iov ) return ENOMEM;

  err = qbuffer_to_iov(buf, start, end, num_parts, iov, NULL, &iovcnt);
  if( err ) goto error;

  for( i = 0; i < iovcnt; i++ ) {
    memset(iov[i].iov_base, byte, iov[i].iov_len);
  }

  MAYBE_STACK_FREE(iov, iov_onstack);
  return 0;

error:
  MAYBE_STACK_FREE(iov, iov_onstack);
  return err;
}
