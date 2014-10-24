#include "deque.h"
#include <assert.h>
#include <stdio.h>

void print_deque(size_t item_size, deque_t* d)
{
  deque_iterator_t cur = deque_begin(d);
  deque_iterator_t end = deque_end(d);
  int j;
  assert(item_size == 4);
  printf("deque %p: d=%p log2=%i s=%li e=%li :: ",
         d, d->data, (int) d->log2_capacity, (long) d->start, (long) d->end);
  while( ! deque_it_equals(cur, end) ) {
    j = 0;
    deque_it_get_cur(item_size, d, cur, &j);
    printf(" %i", j);
    deque_it_forward_one(item_size, &cur);
  }
  printf("\n");
}

void iterate_counting(size_t item_size, deque_t* d, int num)
{
  deque_iterator_t begin = deque_begin(d);
  deque_iterator_t end = deque_end(d);
  deque_iterator_t cur = begin;
  deque_iterator_t test;
  int i = 0;
  int j;
  assert(item_size == 4);
  while( i < num && ! deque_it_equals(cur, end) ) {
    // check that the value is right.
    deque_it_get_cur(item_size, d, cur, &j);
    assert( j == i );
    
    // check that advancing from beginning i elements takes us here.
    test = begin;
    deque_it_forward_n(item_size, &test, i);
    assert( deque_it_equals( test, cur ) );

    // advance to the next element, checking that
    // forward_one is the same as forward_n(1) 
    test = cur;
    deque_it_forward_one(item_size, &cur);
    deque_it_forward_n(item_size, &test, 1);
    assert( deque_it_equals( test, cur ) );
    i++;
  }
}

void check_realloc(int64_t skipping, int nelems, int from_capacity, int to_capacity)
{
  err_t err;
  deque_t d;

  //printf("check_realloc skip=%li nelems=%i fromcap=%i tocap=%i\n", (long) skipping, nelems, from_capacity, to_capacity);

  assert( nelems <= from_capacity );
  assert( nelems <= to_capacity );

  err = deque_init(4, &d, from_capacity);
  assert(!err);
  d.start = skipping;
  d.end = skipping;

  // Fill up our deque with the data...
  {
    int i;
    for( i = 0; i < nelems; i++ ) {
      deque_push_back(4, &d, &i);
    }
  }
  assert( deque_size(4, &d) == nelems );

  // Now read the data in the deque, check it is right.
  iterate_counting(4, &d, nelems);

  //printf("Before realloc\n");
  //print_deque(4, &d);

  // Now do a reallocation
  err = _deque_realloc(4, &d, to_capacity);
  assert(!err);
 
  //printf("After realloc\n");
  //print_deque(4, &d);

  // Now read the data in the deque, check it is right.
  iterate_counting(4, &d, nelems);

  deque_destroy(&d);
}

void test_reallocate(void)
{
  // hit the different reallocate cases.
  int64_t skip;
  int nelems;
  int ncaps = 10;
  int x,y;
  
  check_realloc(1, 8, 8, 8);
  check_realloc(0, 3, 3, 3);

  for( skip = 0; skip < 32; skip++ ) {
    for( nelems = 0; nelems < 32; nelems++ ) {
      for( x = 0; x < ncaps; x++ ) {
        for( y = 0; y < ncaps; y++ ) {
          int usex, usey;
          usex = 1 << x;
          usey = 1 << y;
          if( usex < nelems ) usex = nelems;
          if( usey < nelems ) usey = nelems;
          check_realloc(skip, nelems, usex, usey);
        }
      }
    }
  }
}


void iterate_counting_reverse(size_t item_size, deque_t* d, int num)
{
  deque_iterator_t cur;
  deque_iterator_t first = deque_begin(d);
  deque_iterator_t last;
  deque_iterator_t test;
  int i = 0;
  int j;

  assert(item_size == 4);

  if( num == 0 ) return;
  if( deque_size(item_size, d) == 0 ) return;

  last = deque_last(item_size, d);
  cur = last;
  do {
    // check that the value is right.
    deque_it_get_cur(item_size, d, cur, &j);
    assert( j == i );

    // check that advancing from end -i elements takes us here.
    test = last;
    deque_it_forward_n(item_size, &test, - i);
    assert( deque_it_equals( test, cur ) );

    // advance to the next element, cheking that
    // back_one is the same as forward_n(-1)
    test = cur;
    deque_it_back_one(item_size, &cur);
    deque_it_forward_n(item_size, &test, -1);
    assert( deque_it_equals( test, cur ) );
    i++;
  } while ( i < num && ! deque_it_equals(cur,first) ); 
}

void push_front_counting(size_t item_size, deque_t* d, int num)
{
  int i;
  assert(item_size == 4);
  for( i = 0; i < num; i++ ) {
    deque_push_front(4, d, &i);
  }
}
void push_back_counting(size_t item_size, deque_t* d, int num)
{
  int i;
  assert(item_size == 4);
  for( i = 0; i < num; i++ ) {
    deque_push_back(4, d, &i);
  }
}
void push_both_counting(size_t item_size, deque_t* d, int num)
{
  int i;
  assert(item_size == 4);
  for( i = 0; i < num; i++ ) {
    deque_push_front(4, d, &i);
    deque_push_back(4, d, &i);
  }
}

void pop_back_check_constant(size_t item_size, deque_t* d, int num, int val)
{
  int i;
  int j;
  ssize_t sz = deque_size(item_size, d);
  assert(item_size == 4);
  assert(sz >= num);
  for( i = 0; i < num; i++ ) {
    assert(deque_size(item_size, d) > 0);
    j = 0;
    deque_it_get_cur(4, d, deque_last(item_size, d), &j);
    assert( j == val );
    deque_pop_back(4, d);
  }
}


void pop_front_check_constant(size_t item_size, deque_t* d, int num, int val)
{
  int i;
  int j;
  ssize_t sz = deque_size(item_size, d);
  assert(item_size == 4);
  assert(sz >= num);
  for( i = 0; i < num; i++ ) {
    assert(deque_size(item_size, d) > 0);
    j = 0;
    deque_it_get_cur(4, d, deque_begin(d), &j);
    assert( j == val );
    deque_pop_front(4, d);
  }
}

void pop_front_check_counting(size_t item_size, deque_t* d, int num)
{
  int i;
  int j;
  ssize_t sz = deque_size(item_size, d);
  assert(item_size == 4);
  assert(sz >= num);
  for( i = 0; i < num; i++ ) {
    assert(deque_size(item_size, d) > 0);
    j = 0;
    deque_it_get_cur(4, d, deque_begin(d), &j);
    assert( j == i );
    deque_pop_front(4, d);
  }
}

void pop_front_check_counting_reverse(size_t item_size, deque_t* d, int num)
{
  int i;
  int j;
  ssize_t sz = deque_size(item_size, d);
  assert(item_size == 4);
  assert(sz >= num);
  for( i = num - 1; i >= 0; i-- ) {
    assert(deque_size(item_size, d) > 0);
    j = 0;
    deque_it_get_cur(4, d, deque_begin(d), &j);
    assert( j == i );
    deque_pop_front(4, d);
  }
}

void pop_back_check_counting(size_t item_size, deque_t* d, int num)
{
  int i;
  int j;
  ssize_t sz = deque_size(item_size, d);
  assert(item_size == 4);
  assert(sz >= num);
  for( i = 0; i < num; i++ ) {
    assert(deque_size(item_size, d) > 0);
    j = 0;
    deque_it_get_cur(4, d, deque_last(item_size, d), &j);
    //printf("Got %i\n", j);
    assert( j == i );
    deque_pop_back(4, d);
  }
}

void pop_back_check_counting_reverse(size_t item_size, deque_t* d, int num)
{
  int i;
  int j;
  ssize_t sz = deque_size(item_size, d);
  assert(item_size == 4);
  assert(sz >= num);
  for( i = num - 1; i >= 0; i-- ) {
    assert(deque_size(item_size, d) > 0);
    j = 0;
    deque_it_get_cur(4, d, deque_last(item_size, d), &j);
    assert( j == i );
    deque_pop_back(4, d);
  }
}

void check_empty(size_t item_size, deque_t* d)
{
  ssize_t sz = deque_size(item_size, d);
  assert(item_size == 4);
  assert( sz == 0 );
}

int lots = 1 << 15;

void test_deque(int lots)
{
  deque_t d;
  int i;
  int zero = 0;
  // test: space for zeros.
  deque_init(4, &d, 0);
  check_empty(4, &d);
  deque_destroy(&d);

  // test: space for zeros.
  deque_init(4, &d, 10);
  for( i = 0; i < 10; i++ ) deque_push_front(4, &d, &zero);
  pop_back_check_constant(4, &d, 10, 0);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: space for zeros.
  deque_init(4, &d, 10);
  for( i = 0; i < 10; i++ ) deque_push_back(4, &d, &zero);
  pop_front_check_constant(4, &d, 10, 0);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: push back lots, destroy
  deque_init(4, &d, 0);
  push_back_counting(4, &d, lots);
  iterate_counting(4, &d, lots);
  deque_destroy(&d);
  // test: push back lots, pop front lots.
  deque_init(4, &d, 0);
  push_back_counting(4, &d, lots);
  iterate_counting(4, &d, lots);
  pop_front_check_counting(4, &d, lots);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: push back lots, pop back lots.
  deque_init(4, &d, 0);
  push_back_counting(4, &d, lots);
  pop_back_check_counting_reverse(4, &d, lots);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: push front lots, pop front lots.
  deque_init(4, &d, 0);
  push_front_counting(4, &d, lots);
  iterate_counting_reverse(4, &d, lots);
  //print_deque(4, &d);
  pop_front_check_counting_reverse(4, &d, lots);
  //print_deque(4, &d);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: push front lots, pop back lots.
  deque_init(4, &d, 0);
  push_front_counting(4, &d, lots);
  //print_deque(4, &d);
  pop_back_check_counting(4, &d, lots);
  //print_deque(4, &d);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: push both lots, pop back lots, pop back lots.
  deque_init(4, &d, 0);
  push_both_counting(4, &d, lots);
  //print_deque(4, &d);
  pop_back_check_counting_reverse(4, &d, lots);
  pop_back_check_counting(4, &d, lots);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: push both lots, pop front lots, pop front lots.
  deque_init(4, &d, 0);
  push_both_counting(4, &d, lots);
  //print_deque(4, &d);
  pop_front_check_counting_reverse(4, &d, lots);
  pop_front_check_counting(4, &d, lots);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: push both lots, pop back lots, pop front lots
  deque_init(4, &d, 0);
  push_both_counting(4, &d, lots);
  //print_deque(4, &d);
  pop_back_check_counting_reverse(4, &d, lots);
  pop_front_check_counting_reverse(4, &d, lots);
  check_empty(4, &d);
  deque_destroy(&d);
  // test: push both lots, pop front lots, pop back lots
  deque_init(4, &d, 0);
  push_both_counting(4, &d, lots);
  //print_deque(4, &d);
  pop_front_check_counting_reverse(4, &d, lots);
  pop_back_check_counting_reverse(4, &d, lots);
  check_empty(4, &d);
  deque_destroy(&d);
}

int main(int argc, char** argv)
{
  int i;
  test_reallocate();
  {
    deque_t d;
    int lots = 2;
    deque_init(4, &d, 0);
    push_front_counting(4, &d, lots);
    //print_deque(4, &d);
    pop_back_check_counting(4, &d, lots);
    //print_deque(4, &d);
    check_empty(4, &d);
    deque_destroy(&d);
  }
  for( i = 0; i < 32; i++ ) {
    test_deque(i);
  }
  for( i = 127; i < 512; i++ ) {
    test_deque(i);
  }
  test_deque(1 << 15);

  return 0;
}

