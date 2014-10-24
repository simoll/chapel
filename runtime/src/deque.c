
#ifndef SIMPLE_TEST
#include "chplrt.h"
#endif

#include "deque.h"


#define _DEQUE_MIN(a,b) (a<b?a:b)

static inline
int64_t _deque_posmin2(int64_t a, int64_t b)
{
  if( a > 0 && b > 0 ) return _DEQUE_MIN(a,b);
  if( a <= 0 && b <= 0 ) return 0;
  if( a > 0 ) return a;
  if( b > 0 ) return b;
  return 0;
}

static inline
int64_t _deque_posmin3(int64_t a, int64_t b, int64_t c)
{
  return _deque_posmin2( _deque_posmin2(a,b), c );
}

void debug_print_deque_iter(deque_iterator_t* it)
{
  fprintf(stderr, "deque_it: %li\n", (long) it->cur);
}

// It's important that deque_realloc not deallocate the existing
// data in case there is an error; that way shrinking can always
// avoid returning an error (since the error can be ignored).
err_t _deque_realloc(const ssize_t item_size, deque_t* d, int64_t min_capacity)
{
  int64_t new_log2_capacity = _deque_log2_capacity_for(min_capacity);
  int64_t one = 1;
  int64_t new_capacity = one << new_log2_capacity;
  int64_t old_capacity = one << d->log2_capacity;
  void* new_data;
  int64_t old_end_capacity;
  int64_t new_end_capacity;
  int64_t copied;
  int64_t to_copy;
  int64_t src_off;
  int64_t dst_off;
  int64_t need;

  new_data = deque_calloc(new_capacity, item_size);
  if( ! new_data ) return ENOMEM;

  old_end_capacity = old_capacity +
                     d->start - _deque_get_offset(d->log2_capacity, d->start);
  new_end_capacity = new_capacity +
                     d->start - _deque_get_offset(new_log2_capacity, d->start);

  // Generally, we have to do this copy in 4 parts.
  copied = 0;
  need = d->end - d->start;
  while( copied < need ) {
    to_copy = _deque_posmin3(d->end - (d->start + copied),
                             old_end_capacity - (d->start + copied),
                             new_end_capacity - (d->start + copied));

    src_off = _deque_get_byte_offset(item_size, d->log2_capacity, d->start+copied);
    dst_off = _deque_get_byte_offset(item_size, new_log2_capacity, d->start+copied);
    memcpy(PTR_ADDBYTES(new_data, dst_off),
           PTR_ADDBYTES(d->data, src_off),
           to_copy * item_size);

    copied += to_copy;
  }

  deque_free(d->data);
  d->data = new_data;
  d->log2_capacity = new_log2_capacity;
  // leave start, end alone.

  return 0;
}


