/* A simple deque made up a doubling circular array.
 */

#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "sys_basic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef _chplrt_H_
#include "chpl-mem.h"
#define deque_calloc(nmemb, size) chpl_mem_allocManyZero( nmemb, size, CHPL_RT_MD_IO_BUFFER, __LINE__, __FILE__ )
#define deque_free(ptr) chpl_mem_free(ptr, __LINE__, __FILE__)
#else
#define deque_calloc(nmemb, size) calloc(nmemb,size)
#define deque_free(ptr) free(ptr)
#endif

typedef struct deque_iterator_s {
  int64_t cur; // absolute offset in items
} deque_iterator_t;

void debug_print_deque_iter(deque_iterator_t* it);

static inline
deque_iterator_t deque_iterator_null(void) {
  deque_iterator_t ret;
  ret.cur = 0;
  return ret;
}

typedef struct deque_s {
  void* data;
  size_t log2_capacity; // ie data is (1 << capacity_bits) * itemsize bytes
  int64_t start; // absolute offset in items
  int64_t end; // absolute offset in items
} deque_t;

#define _DEQUE_INITIAL_SIZE 4

#define _DEQUE_MAX(a,b) (a>b?a:b)

static inline
void deque_it_forward_one(const ssize_t item_size, deque_iterator_t* it)
{
  it->cur++;
}

static inline
void deque_it_back_one(const ssize_t item_size, deque_iterator_t* it)
{
  it->cur--;
}

// advance n items.
static inline
void deque_it_forward_n(const ssize_t item_size, deque_iterator_t* it, ssize_t n)
{
  it->cur += n;
}

static inline
int64_t _deque_capacity(deque_t* d)
{
  int64_t ret = 1;
  return ret << d->log2_capacity;
}

static inline
int64_t _deque_get_offset(size_t log2_capacity, int64_t cur)
{
  int64_t local_offset;
  int64_t mask;

  local_offset = cur;
  mask = 1;
  mask <<= log2_capacity;
  mask--;
  local_offset &= mask;

  return local_offset;
}


static inline
int64_t _deque_get_byte_offset(const ssize_t item_size, size_t log2_capacity, int64_t cur)
{
  return _deque_get_offset(log2_capacity, cur) * item_size;
}


static inline
void* _deque_get_ptr(const ssize_t item_size, const deque_t* d, int64_t cur)
{
  int64_t local_offset_bytes;
  void* ptr;

  local_offset_bytes = _deque_get_byte_offset(item_size, d->log2_capacity, cur);

  ptr = PTR_ADDBYTES(d->data, local_offset_bytes);
  return ptr;
}


// Not safe against deque-modifying operations
// (ie if you push or pop, the pointer may become invalid
//  because the deque resized)
static inline
void* deque_it_get_cur_ptr(const ssize_t item_size, const deque_t* deque, const deque_iterator_t it)
{
  return _deque_get_ptr(item_size, deque, it.cur);
}

static inline
void deque_it_get_cur(const ssize_t item_size, const deque_t* deque, const deque_iterator_t it, void* out)
{
  void* ptr = deque_it_get_cur_ptr(item_size, deque, it);
  memcpy(out, ptr, item_size);
}

static inline
void deque_it_set_cur(const ssize_t item_size, const deque_t* deque, const deque_iterator_t it, void* in)
{
  void* ptr = deque_it_get_cur_ptr(item_size, deque, it);
  memcpy(ptr, in, item_size);
}

static inline
char deque_it_equals(const deque_iterator_t a, const deque_iterator_t  b)
{
  return a.cur == b.cur;
}

static inline
ssize_t deque_it_difference(const ssize_t item_size, const deque_iterator_t x, const deque_iterator_t y)
{
  return x.cur - y.cur;
}

static inline
int64_t _deque_log2_capacity_for(int64_t num_elements)
{
  int64_t nitems = _DEQUE_MAX(_DEQUE_INITIAL_SIZE, num_elements);
  int64_t log2_capacity = 1;
  while( (((int64_t)1) << log2_capacity) < nitems ) log2_capacity++;
  return log2_capacity;
}

static inline
err_t deque_init(const ssize_t item_size, deque_t* d, ssize_t capacity_elts)
{
  // round up to a power of 2
  d->log2_capacity = _deque_log2_capacity_for(capacity_elts);
  d->data = deque_calloc(_deque_capacity(d), item_size);
  if( ! d->data ) return ENOMEM;
  d->start = 0;
  d->end = 0;
  return 0;
}

static inline
void deque_destroy(deque_t* d)
{
  deque_free(d->data);
  // Clear any pointers we had left over...
  d->data = NULL;
}

static inline
void deque_init_uninitialized(deque_t* d)
{
  d->data = NULL;
}

static inline
int deque_is_initialized(deque_t* d)
{
  return d->data != NULL;
}

static inline
deque_iterator_t deque_begin(deque_t* d)
{
  deque_iterator_t ret;
  ret.cur = d->start;
  return ret;
}

static inline
deque_iterator_t deque_end(deque_t* d)
{
  deque_iterator_t ret;
  ret.cur = d->end;
  return ret;
}

static inline
deque_iterator_t deque_last(const ssize_t item_size, deque_t* d)
{
  deque_iterator_t ret;
  ret.cur = d->end;
  deque_it_back_one(item_size, &ret);
  return ret;
}


static inline
ssize_t deque_size(const ssize_t item_size, deque_t* d)
{
  return d->end - d->start;
}

// These functions are in the C file.
// If reallocation fails, we return an error but do not deallocate
// the old deque.
err_t _deque_realloc(const ssize_t item_size, deque_t* d, int64_t min_capacity);

static inline
err_t _deque_reserve(const ssize_t item_size, deque_t* d, ssize_t nodes_to_add)
{
  if( (d->end + nodes_to_add - d->start) > _deque_capacity(d) ) {
    return _deque_realloc(item_size, d, d->end + nodes_to_add - d->start);
  } else {
    return 0;
  }
}

static inline
err_t deque_push_front(const ssize_t item_size, deque_t* d, void* value)
{
  void* ptr;
  err_t err;
  err = _deque_reserve(item_size, d, 1);
  if( ! err ) {
    d->start--;
    ptr = _deque_get_ptr(item_size, d, d->start);
    memcpy(ptr, value, item_size);
  }
  return err;
}

static inline
err_t deque_push_back(const ssize_t item_size, deque_t* d, void* value)
{
  void* ptr;
  err_t err;
  err = _deque_reserve(item_size, d, 1);
  if( ! err ) {
    ptr = _deque_get_ptr(item_size, d, d->end);
    d->end++;
    memcpy(ptr, value, item_size);
  }
  return err;
}

static inline
err_t _deque_maybeshrink(const ssize_t item_size, deque_t* d)
{
  if( (d->end - d->start) < _deque_capacity(d)/4 ) {
    return _deque_realloc(item_size, d, _deque_capacity(d)/2);
  } else {
    return 0;
  }
}

// errors from deque_pop_front and deque_pop_back can safely be ignored.
static inline
err_t deque_pop_front(const ssize_t item_size, deque_t* d)
{
  d->start++;
  return _deque_maybeshrink(item_size, d);
}

static inline
err_t deque_pop_back(const ssize_t item_size, deque_t* d)
{
  d->end--;
  return _deque_maybeshrink(item_size, d);
}

#endif
