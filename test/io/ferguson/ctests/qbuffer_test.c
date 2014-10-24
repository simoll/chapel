#include "qbuffer.h"
#include <assert.h>

extern int64_t _qbuffer_get_block(qbuffer_t* buf, int64_t offset, int* block_bits_out);
extern int _qbuffer_log2_next(int64_t size, int milog2);

void test_qbytes(void)
{
  qbytes_t* b;
  int err;

  // easiest test -- create and release.
  err = qbytes_create_iobuf(&b);
  assert(!err);

  qbytes_release(b);

  // test 2 -- create, retain, release, release.
  err = qbytes_create_iobuf(&b);
  assert(!err);

  qbytes_retain(b);

  qbytes_release(b);

  qbytes_release(b);

  // test 3 -- create a particular length.
  err = qbytes_create_calloc(&b, 2000);
  assert(!err);

  assert( b->len == 2000 );

  qbytes_release(b);
}

void test_qbuffer_iterators(qbuffer_t* buf, qbytes_t** qb, int num, int skip, int trunc)
{
  qbuffer_iter_t cur;
  qbuffer_iter_t search;
  qbuffer_iter_t start;
  qbuffer_iter_t end;
  int i,j;
  int64_t off;
  int64_t total_len;

  total_len = 0;
  for( i = 0; i < num; i++ ) {
    total_len += qb[i]->len - skip - trunc;
  }
  assert( total_len == qbuffer_len(buf) );

  start = qbuffer_begin(buf);
  end = qbuffer_end(buf);

  i = 0;
  cur = start;
  // now try iterating through them
  while( ! qbuffer_iter_same_part(cur, end) ) {
    int64_t skip, len;
    qbytes_t* bytes;

    qbuffer_iter_get_items(buf, cur, end, &bytes, &skip, &len);
    assert( bytes == qb[i] );
    assert( skip == skip );
    assert( len == qb[i]->len - skip - trunc );

    qbuffer_iter_next_part(buf, &cur);

    i++;
  }
 
  // now try iterating through them backwards.
  if( ! qbuffer_iter_same_part(start, end) ) {
    i = num - 1;
    cur = end;
    do {
      int64_t skip, len;
      qbytes_t* bytes;

      qbuffer_iter_prev_part(buf, &cur);

      qbuffer_iter_get_items(buf, cur, end, &bytes, &skip, &len);
      assert( bytes == qb[i] );
      assert( skip == skip );
      assert( len == qb[i]->len - skip - trunc );

      i--;
    } while( ! qbuffer_iter_same_part(cur, start) );
  }

  // check qbuffer_flatten, qbuffer_copyout, qbuffer_copyin, advance, get
  {
    qbytes_t* flat;
    qbytes_t* flat2;
    qbytes_t* zeros;
    int err;

    err = qbuffer_flatten(buf, start, end, &flat);
    assert(!err);

    // check that flat has the right data in it.
    j = 0;
    for( i = 0; i < num; i++ ) {
      assert( 0 == memcmp(flat->data + j, qb[i]->data + skip, qb[i]->len - skip - trunc) );
      j += qb[i]->len - skip - trunc;
    }
    assert( qbuffer_len(buf) == j );

    // Try flattening the buffer with advanced iterators.
    if( qbuffer_len(buf) > 2 ) {
      cur = start;
      search = end;
      qbuffer_iter_advance(buf, &cur, 1);
      qbuffer_iter_advance(buf, &search, -1);

      err = qbuffer_flatten(buf, cur, search, &flat2);
      assert(!err);

      j = 0;
      for( i = 0; i < num; i++ ) {
        int64_t sk = skip;
        int64_t ln = qb[i]->len - skip - trunc;
        if( i == 0 ) {
          // take one byte off the front of the first one..
          sk++;
          ln--;
        }
        if( i == num - 1 ) {
          // take one byte off the end of the last one.
          ln--;
        }
        if( ln > 0 ) {
          assert( 0 == memcmp(flat2->data + j, qb[i]->data + sk, ln) );
          j += ln;
        }
      }
      assert( qbuffer_len(buf) - 2 == j );

      qbytes_release(flat2);
    }

    // now try advancing forward through the buffer, checking every byte.
    cur = start;
    j = 0;
    while( ! qbuffer_iter_equals(cur, end) ) {
      qbytes_t* tmp;
      int64_t skip, len;

      qbuffer_iter_get_items(buf, cur, end, &tmp, &skip, &len);
      assert( 0 == memcmp(tmp->data + skip, flat->data + j, 1) );

      // check that binary search would lead us here too.
      search = qbuffer_iter_at(buf, cur.offset);
      assert( qbuffer_iter_equals( search, cur ) );
      assert( qbuffer_iter_same_part( search, cur ) );

      qbuffer_iter_advance(buf, &cur, 1);
      j++;
    }

    // now try advancing backward through the buffer, checking every byte.
    if( ! qbuffer_iter_equals(start, end) ) {
      cur = end;
      j = flat->len - 1;
      do {
        qbytes_t* tmp;
        int64_t skip, len;

        qbuffer_iter_advance(buf, &cur, -1);

        qbuffer_iter_get_items(buf, cur, end, &tmp, &skip, &len);
        assert( 0 == memcmp(tmp->data + skip, flat->data + j, 1) );

        j--;
      } while( ! qbuffer_iter_equals(cur, start) );
    }

    // overwrite it with zeros.
    err = qbuffer_memset(buf, start, end, 0);
    assert(!err);

    err = qbuffer_flatten(buf, start, end, &zeros);
    assert(!err);

    for( off = 0; off < zeros->len; off++ ) {
      unsigned char byte = * (unsigned char*) (zeros->data + off);
      assert(byte == 0);
    }

    qbytes_release(zeros);

    // now copy the data back in.
    err = qbuffer_copyin(buf, start, end, flat->data, flat->len);
    assert(!err);

    err = qbuffer_flatten(buf, start, end, &flat2);
    assert(!err);

    assert( flat->len == flat2->len );
    assert( 0 == memcmp(flat->data, flat2->data, flat->len) );


    // clear flat
    memset(flat->data, 0, flat->len);

    // now copy the data back out.
    err = qbuffer_copyout(buf, start, end, flat->data, flat->len);
    assert(!err);

    assert( flat->len == flat2->len );
    assert( 0 == memcmp(flat->data, flat2->data, flat->len) );

    qbytes_release(flat2);
    qbytes_release(flat);
  }
  

}

void test_qbuffer_with(qbytes_t** qb, int num, int skip, int trunc)
{
  qbuffer_t buf;
  int err;
  int i;
  int j;

  err = qbuffer_init(&buf);
  assert(!err);

  // try appending them all.
  for( i = 0; i < num; i++ ) {
    err = qbuffer_append(&buf, qb[i], skip, qb[i]->len - skip - trunc, 0);
    assert(!err);
  }

  test_qbuffer_iterators(&buf, qb, num, skip, trunc);

  qbuffer_destroy_inplace(&buf);



  err = qbuffer_init(&buf);
  assert(!err);

  // try prepending them all.
  for( i = num - 1; i >= 0; i-- ) {
    err = qbuffer_prepend(&buf, qb[i], skip, qb[i]->len - skip - trunc, 0);
    assert(!err);
  }

  test_qbuffer_iterators(&buf, qb, num, skip, trunc);

  qbuffer_destroy_inplace(&buf);


  err = qbuffer_init(&buf);
  assert(!err);

  // try appending/prepending alternating
  // i is prepending index, j is appending index
  for( i = num / 2 - 1, j = i+1; i >= 0 || j < num; i--, j++ ) {
    if( i >= 0 ) {
      err = qbuffer_prepend(&buf, qb[i], skip, qb[i]->len - skip - trunc, 0);
      assert(!err);
    }
    if( j < num ) {
      err = qbuffer_append(&buf, qb[j], skip, qb[j]->len - skip - trunc, 0);
      assert(!err);
    }
  }

  test_qbuffer_iterators(&buf, qb, num, skip, trunc);

  qbuffer_destroy_inplace(&buf);
}

void fill_test_data(qbytes_t* b, int testnum)
{
  int64_t i;
  unsigned char* data = b->data;

  for( i = 0; i < b->len; i++ ) {
    data[i] = 50 * testnum  + (i % 50);
  }
}

void test_qbuffer(void)
{
  // create a qbuffer.
  qbuffer_t buf;
  qbytes_t* b[8];
  int i,j, skip, trunc;
  int err;
  int maxskip = 3;
  int maxtrunc = 3;

  err = qbuffer_init(&buf);
  assert(!err);

  qbuffer_destroy_inplace(&buf);

  // create some bytes objects...
  i = 0;
  err = qbytes_create_calloc(&b[i], 10);
  assert(!err);
  fill_test_data(b[i], i);
  i++;

  err = qbytes_create_calloc(&b[i], 20);
  assert(!err);
  fill_test_data(b[i], i);
  i++;

  err = qbytes_create_calloc(&b[i], 30);
  assert(!err);
  fill_test_data(b[i], i);
  i++;

  err = qbytes_create_calloc(&b[i], 40);
  assert(!err);
  fill_test_data(b[i], i);
  i++;

  for( j = 0; j < i; j++ ) {
    for( skip = 0; skip < maxskip; skip++ ) {
      for( trunc = 0; trunc < maxtrunc; trunc++ ) {
        test_qbuffer_with(b, j, skip, trunc);
      }
    }
  }

  for( j = 0; j < i; j++ ) {
    qbytes_release(b[j]);
  }
}

void test_qbuffer_two(void)
{
  // We create two buffers and call 
  // copyin_buffer
  qbuffer_t bufa, bufb, bufab1, bufab2;
  qbytes_t* b[8];
  qbytes_t* a[8];
  qbytes_t* bufa_flat;
  qbytes_t* bufb_flat;
  qbytes_t* bufab1_flat;
  qbytes_t* bufab2_flat;
  qbytes_t* bufb2_flat;
  int i,j, x,y;
  err_t err;

  // create some bytes objects...
  i = 0;
  err = qbytes_create_calloc(&b[i], 10);
  assert(!err);
  fill_test_data(b[i], i);
  i++;

  err = qbytes_create_calloc(&b[i], 20);
  assert(!err);
  fill_test_data(b[i], i);
  i++;

  err = qbytes_create_calloc(&b[i], 30);
  assert(!err);
  fill_test_data(b[i], i);
  i++;

  err = qbytes_create_calloc(&b[i], 40);
  assert(!err);
  fill_test_data(b[i], i);
  i++;

  // create some bytes objects...
  x = 0;
  err = qbytes_create_calloc(&a[x], 10);
  assert(!err);
  fill_test_data(a[x], x);
  x++;

  err = qbytes_create_calloc(&a[x], 7);
  assert(!err);
  fill_test_data(a[x], x);
  x++;

  err = qbytes_create_calloc(&a[x], 29);
  assert(!err);
  fill_test_data(a[x], x);
  x++;

  err = qbytes_create_calloc(&a[x], 100);
  assert(!err);
  fill_test_data(a[x], x);
  x++;


  err = qbuffer_init(&bufa);
  assert(!err);
  err = qbuffer_init(&bufb);
  assert(!err);
  err = qbuffer_init(&bufab1);
  assert(!err);
  err = qbuffer_init(&bufab2);
  assert(!err);

  for( j = 0; j < i; j++ ) {
    err = qbuffer_append(&bufb, b[j], 0, b[j]->len, 0);
    assert(!err);
  }
  for( y = 0; y < x; y++ ) {
    err = qbuffer_append(&bufa, a[y], 0, a[y]->len, 0);
    assert(!err);
  }

  err = qbuffer_flatten(&bufa, qbuffer_begin(&bufa), qbuffer_end(&bufa), &bufa_flat);
  assert(!err);

  err = qbuffer_flatten(&bufb, qbuffer_begin(&bufb), qbuffer_end(&bufb), &bufb_flat);
  assert(!err);

  // construct ab1 with append
  err = qbuffer_append(&bufab1, bufa_flat, 0, bufa_flat->len, 0);
  assert(!err);
  err = qbuffer_append(&bufab1, bufb_flat, 0, bufb_flat->len, 0);
  assert(!err);
  
  err = qbuffer_flatten(&bufab1, qbuffer_begin(&bufab1), qbuffer_end(&bufab1), &bufab1_flat);
  assert(!err);

  // construct ab2 with qbuffer_append_buffer
  err = qbuffer_append_buffer(&bufab2, &bufa, qbuffer_begin(&bufa), qbuffer_end(&bufa), 0);
  assert(!err);
  err = qbuffer_append_buffer(&bufab2, &bufb, qbuffer_begin(&bufb), qbuffer_end(&bufb), 0);
  assert(!err);

  err = qbuffer_flatten(&bufab2, qbuffer_begin(&bufab2), qbuffer_end(&bufab2), &bufab2_flat);
  assert(!err);

  assert( bufab1_flat->len == bufab2_flat->len);
  assert( 0 == memcmp(bufab1_flat->data, bufab2_flat->data, bufab1_flat->len) );

  {
    qbuffer_iter_t end = qbuffer_begin(&bufab1);
    qbuffer_iter_advance(&bufab1, &end, qbuffer_len(&bufb));

    // Now try overwriting some data in bufab1 with the data in bufb.
    err = qbuffer_copyin_buffer(&bufab1, qbuffer_begin(&bufab1), end,
                                &bufb, qbuffer_begin(&bufb), qbuffer_end(&bufb));
    assert(!err);

    // Now check that bufab1 starts with b.
    err = qbuffer_flatten(&bufab1, qbuffer_begin(&bufab1), end, &bufb2_flat);
    assert(!err);

    assert( bufb2_flat->len == bufb_flat->len);
    assert( 0 == memcmp(bufb_flat->data, bufb2_flat->data, bufb_flat->len) );
  }

  qbytes_release(bufa_flat);
  qbytes_release(bufb_flat);
  qbytes_release(bufab1_flat);
  qbytes_release(bufab2_flat);
  qbytes_release(bufb2_flat);

  qbuffer_destroy_inplace(&bufb);
  qbuffer_destroy_inplace(&bufa);
  qbuffer_destroy_inplace(&bufab1);
  qbuffer_destroy_inplace(&bufab2);

  for( j = 0; j < i; j++ ) {
    qbytes_release(b[j]);
  }
  for( y = 0; y < x; y++ ) {
    qbytes_release(a[y]);
  }
}

static inline
uint8_t test_byte(int at)
{
  return at % 127;
}

void fill_test_seq(qbytes_t* b, int start)
{
  int64_t i;
  unsigned char* data = b->data;

  for( i = 0; i < b->len; i++ ) {
    data[i] = test_byte(start + i);
  }
}


void test_qbuffer_growing(qbuffer_type_t type, int phase, int start_size, int append_amount, int trim_back, int trim_front)
{
  err_t err;
  qbuffer_t buf;
  int i;
  int start_value = 0;

  //printf("growing type %i phase %i start %i append %i trimb %i trimf %i\n", type, phase, start_size, append_amount, trim_back, trim_front);

  err = qbuffer_init_type(&buf, type);
  assert(!err);

  qbuffer_reposition(&buf, phase);

  // Put in data... of start_size.
  if( start_size > 0 ) {
    qbytes_t* start;
    err = qbytes_create_calloc(&start, start_size);

    assert(!err);
    fill_test_seq(start, start_value);

    qbuffer_append(&buf, start, 0, start_size, QB_PART_FLAGS_REST_MUTABLE|QB_PART_FLAGS_MUTABLE);

    qbytes_release(start);
  }
  // make sure type did not change.
  assert( buf.type == type );

  // now append append_amount with grow
  for( i = 0; i < append_amount; i++ ) {
    err = qbuffer_grow_back(&buf, 1, 0);
    assert(!err);
    assert( buf.type == type );
    assert( qbuffer_len(&buf) == 1 + start_size + i);

    {
      qbuffer_iter_t end = qbuffer_end(&buf);
      qbuffer_iter_t prev = end;
      qbuffer_iter_advance(&buf, &prev, -1);

      err = qbuffer_memset(&buf, prev, end, test_byte(start_value + start_size + i));
      assert(!err);
    }
  }

  // now trim from the back.
  qbuffer_shrink_back(&buf, trim_back);

  assert( buf.type == type );

  // now trim from the front
  qbuffer_trim_front(&buf, trim_front);

  assert( buf.type == type );

  //debug_print_qbuffer(&buf);

  // Now verify the data.
  {
    int start_offset, end_offset, cur_value;
    uint8_t byte;

    start_offset = phase + trim_front;
    end_offset = phase + start_size + append_amount - trim_back;
    cur_value = start_value + trim_front;

    for( i = start_offset; i < end_offset; i++ ) {
      qbuffer_iter_t from, to, check;
      from = to = qbuffer_iter_at(&buf, i);
      qbuffer_iter_advance(&buf, &to, 1);

      check = qbuffer_begin(&buf);
      qbuffer_iter_advance(&buf, &check, i - qbuffer_start_offset(&buf));

      assert( qbuffer_iter_equals(from, check) );
      assert( qbuffer_iter_same_part(from, check) );

      byte = 0;

      err = qbuffer_copyout(&buf, from, to, &byte, 1);
      assert(!err);

      assert( byte == test_byte(cur_value) );
      cur_value++;
    }
  }

  qbuffer_destroy_inplace(&buf);
}

void test_qbuffer_computation(void)
{
  qbuffer_t buf;
  err_t err;
  int block_bits;
  int64_t block_index;

  assert(_qbuffer_log2_next(0, 0) == 0);
  assert(_qbuffer_log2_next(1, 0) == 0);
  assert(_qbuffer_log2_next(2, 0) == 1);
  assert(_qbuffer_log2_next(0, 1) == 1);
  assert(_qbuffer_log2_next(1, 1) == 1);
  assert(_qbuffer_log2_next(2, 1) == 1);
  assert(_qbuffer_log2_next(3, 0) == 3);
  assert(_qbuffer_log2_next(4, 0) == 2);
  assert(_qbuffer_log2_next(7, 0) == 4);
  assert(_qbuffer_log2_next(8, 0) == 3);

  err = qbuffer_init_type(&buf, QB_OTHER);
  assert(!err);

  buf.type = QB_EVEN;
  buf.log2_items_starting = 0;
  block_index = _qbuffer_get_block(&buf, 0, &block_bits);
  assert( block_index == 0 && block_bits == 0 );
  block_index = _qbuffer_get_block(&buf, 1, &block_bits);
  assert( block_index == 1 && block_bits == 0 );
  block_index = _qbuffer_get_block(&buf, 2, &block_bits);
  assert( block_index == 2 && block_bits == 0 );
  block_index = _qbuffer_get_block(&buf, 3, &block_bits);
  assert( block_index == 3 && block_bits == 0 );

  buf.type = QB_EVEN;
  buf.log2_items_starting = 1;
  block_index = _qbuffer_get_block(&buf, 0, &block_bits);
  assert( block_index == 0 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 1, &block_bits);
  assert( block_index == 0 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 2, &block_bits);
  assert( block_index == 1 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 3, &block_bits);
  assert( block_index == 1 && block_bits == 1 );

  buf.type = QB_POWERS;
  buf.log2_items_starting = 0;
  block_index = _qbuffer_get_block(&buf, 0, &block_bits);
  assert( block_index == 0 && block_bits == 0 );

  block_index = _qbuffer_get_block(&buf, 1, &block_bits);
  assert( block_index == 1 && block_bits == 0 );

  block_index = _qbuffer_get_block(&buf, 2, &block_bits);
  assert( block_index == 2 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 3, &block_bits);
  assert( block_index == 2 && block_bits == 1 );

  block_index = _qbuffer_get_block(&buf, 4, &block_bits);
  assert( block_index == 3 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 5, &block_bits);
  assert( block_index == 3 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 6, &block_bits);
  assert( block_index == 4 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 7, &block_bits);
  assert( block_index == 4 && block_bits == 1 );

  block_index = _qbuffer_get_block(&buf, 8, &block_bits);
  assert( block_index == 5 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 9, &block_bits);
  assert( block_index == 5 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 10, &block_bits);
  assert( block_index == 5 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 11, &block_bits);
  assert( block_index == 5 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 12, &block_bits);
  assert( block_index == 6 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 13, &block_bits);
  assert( block_index == 6 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 14, &block_bits);
  assert( block_index == 6 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 15, &block_bits);
  assert( block_index == 6 && block_bits == 2 );

  buf.type = QB_POWERS;
  buf.log2_items_starting = 1;
  block_index = _qbuffer_get_block(&buf, 0, &block_bits);
  assert( block_index == 0 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 1, &block_bits);
  assert( block_index == 0 && block_bits == 1 );

  block_index = _qbuffer_get_block(&buf, 2, &block_bits);
  assert( block_index == 1 && block_bits == 1 );
  block_index = _qbuffer_get_block(&buf, 3, &block_bits);
  assert( block_index == 1 && block_bits == 1 );

  block_index = _qbuffer_get_block(&buf, 4, &block_bits);
  assert( block_index == 2 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 5, &block_bits);
  assert( block_index == 2 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 6, &block_bits);
  assert( block_index == 2 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 7, &block_bits);
  assert( block_index == 2 && block_bits == 2 );

  block_index = _qbuffer_get_block(&buf, 8, &block_bits);
  assert( block_index == 3 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 9, &block_bits);
  assert( block_index == 3 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 10, &block_bits);
  assert( block_index == 3 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 11, &block_bits);
  assert( block_index == 3 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 12, &block_bits);
  assert( block_index == 4 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 13, &block_bits);
  assert( block_index == 4 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 14, &block_bits);
  assert( block_index == 4 && block_bits == 2 );
  block_index = _qbuffer_get_block(&buf, 15, &block_bits);
  assert( block_index == 4 && block_bits == 2 );

  block_index = _qbuffer_get_block(&buf, 16, &block_bits);
  assert( block_index == 5 && block_bits == 3 );
}

void test_qbuffer_grows(void)
{
  int phase, start_size, append_amount, trim_back, trim_front;

  for( phase = -10; phase < 20; ) {
    for( start_size = 0; start_size < 30; ) {
      printf("phase %i start %i\n", phase, start_size);
      for( append_amount = 0; append_amount < 40; ) {
        int size = start_size + append_amount;
        int max_front = size / 2;
        int max_back = size / 2;

        test_qbuffer_growing(QB_OTHER, phase, start_size, append_amount, 0, 0);
        test_qbuffer_growing(QB_EVEN, phase, start_size, append_amount, 0, 0);
        if( phase >= 0 )
          test_qbuffer_growing(QB_POWERS, phase, start_size, append_amount, 0, 0);
 
        for( trim_back = 1; trim_back < max_back; trim_back++ ) {
          for( trim_front = 1; trim_front < max_front; trim_front++ ) {
            test_qbuffer_growing(QB_OTHER, phase, start_size, append_amount, trim_back, trim_front);
            test_qbuffer_growing(QB_EVEN, phase, start_size, append_amount, trim_back, trim_front);
            if( phase >= 0 )
              test_qbuffer_growing(QB_POWERS, phase, start_size, append_amount, trim_back, trim_front);
          }
        }

        if( append_amount < 18 ) append_amount++;
        else append_amount += 7;
      }
      if( start_size < 18 ) start_size++;
      else start_size += 5;
    }
    if( phase > -3 && phase < 3 ) phase++;
    else phase += 3;
  }
}

int main(int argc, char** argv)
{
  qbytes_iobuf_size = 16;
  qbytes_smallbuf_size = 2;

  test_qbytes();
  test_qbuffer();
  test_qbuffer_two();
  test_qbuffer_computation();

  test_qbuffer_growing(QB_POWERS, 0, 1, 1, 0, 0);
  //test_qbuffer_growing(QB_EVEN, 1, 0, 19, 0, 0);
  //test_qbuffer_growing(QB_POWERS, 1, 0, 3, 0, 0);


  test_qbuffer_grows();

  return 0;
}

