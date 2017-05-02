
//#include <limits.h>
#include <pthread.h>

  #include <stdlib.h>
  #include <stdio.h>
#ifndef CHPL_RT_UNIT_TEST
  #include "stdchplrt.h"
#endif
  #include "qio_regexp.h"
  #include "qbuffer.h" // qio_strdup, refcount functions, qio_ptr_diff, etc
  #include "qio.h" // for channel operations
  #undef printf

#include "tre/tre.h"

struct re_cache;

typedef struct re_s {
  regex_t r;
  char* pat;
  int64_t pat_len;
  int errcode;

  // TODO: options
  qbytes_refcnt_t ref_cnt;
} re_t;

// A very simple 8-element local regexp cache.
#define REGEXP_CACHE_SIZE 8
typedef struct cache_elem_s {
  int64_t date;
  re_t* re;
} cache_elem_t;

typedef struct re_cache_s {
  int64_t date;
  cache_elem_t elems[REGEXP_CACHE_SIZE];
} re_cache_t;

static pthread_key_t key;
static pthread_once_t key_once = PTHREAD_ONCE_INIT;

static
void make_key(void)
{
  (void) pthread_key_create(&key, NULL);
}

static inline
re_cache_t* local_cache(void)
{
  re_cache_t* ptr;
  (void) pthread_once(&key_once, make_key);
  if((ptr = (re_cache_t*) pthread_getspecific(key)) == NULL) {
    ptr = (re_cache_t*) qio_malloc(sizeof(re_cache_t));
    memset(ptr, 0, sizeof(re_cache_t));
    (void) pthread_setspecific(key, ptr);
  }
  return ptr;
}

static
void re_free(re_t* re)
{
  if (re) {
    tre_regfree(&re->r);
    qio_free(re);
  }
}


static
re_t* local_cache_get(const char* str, int64_t str_len, const qio_regexp_options_t* options) {
  re_cache_t* c = local_cache();
  int oldest;
  int64_t oldest_date;
  c->date++;
  // Find either the oldest element
  // or a matching element
  oldest = 0;
  oldest_date = c->elems[0].date;
  for( int i = 0; i < REGEXP_CACHE_SIZE; i++ ) {
    const char* pat = c->elems[i].re->pat;
    int64_t pat_len = c->elems[i].re->pat_len;
    if( c->elems[i].date < oldest_date ) {
      oldest = i;
      oldest_date = c->elems[i].date;
    }
    if( ! c->elems[i].re ) continue;
    // TODO options
    if( pat_len == str_len &&
        0 == memcmp(pat, str, str_len ) /*&&
        equal_options(&opt, options) */) {
      // Return this element.
      re_t* re = c->elems[i].re;
      // Make the date current.
      c->elems[i].date = c->date;
      // We increment the reference count before returning a copy to the
      // caller.  It is up to the caller to release the re_t handle when done.
      DO_RETAIN(re);
      return re;
    }
  }

  // If we found no match, replace oldest.
  if( c->elems[oldest].re) DO_RELEASE(c->elems[oldest].re, re_free);

  // Put a new RE in that slot.
  {
    // TODO options
    re_t* re = qio_calloc(sizeof(re_t), 1);
    int rc = tre_regncomp(&re->r, str, str_len, REG_EXTENDED);
    re->pat = qio_calloc(str_len+1, 1);
    memcpy(re->pat, str, str_len);
    re->pat[str_len] = '\0';
    re->pat_len = str_len;
    re->errcode = rc;
    DO_INIT_REFCNT(re);
    
    c->elems[oldest].date = c->date;
    c->elems[oldest].re = re;
    // We increment the reference count before returning a copy to the
    // caller.  It is up to the caller to release the re_t handle when done.
    DO_RETAIN(re);
    return re;
  }
}



void qio_regexp_init_default_options(qio_regexp_options_t* opt)
{
  opt->utf8 = true;
  opt->posix = false;
  opt->literal = false;
  opt->nocapture = false;
  opt->ignorecase = false;
  opt->multiline = false;
  opt->dotnl = false;
  opt->nongreedy = false;
}

// The returned re_t (passed back through "compiled") must be released by the caller.
void qio_regexp_create_compile(const char* str, int64_t str_len, const qio_regexp_options_t* options, qio_regexp_t* compiled)
{
  re_t* regexp = local_cache_get(str, str_len, options);
  compiled->regexp = (void*) regexp;
  // We bump the reference count, because caller "owns" its copy of the cached
  // regexp.  This way, a regexp can be removed from the cache without causing a
  // copy that is still in use to be deleted early.
  DO_RETAIN(regexp);
}

// The re_t returned in compiled must be released by the caller.
void qio_regexp_create_compile_flags(const char* str, int64_t str_len, const char* flags, int64_t flags_len, qio_bool isUtf8, qio_regexp_t* compiled)
{
  qio_regexp_options_t opt;
  qio_regexp_init_default_options(&opt);
  // Parse the flags into options.
  for(int i = 0; i < flags_len; i++ ) {
    if( flags[i] == 'i' ) opt.ignorecase = true;
    if( flags[i] == 'm' ) opt.multiline = true;
    if( flags[i] == 's' ) opt.dotnl = true;
    if( flags[i] == 'U' ) opt.nongreedy = true;
  }
  opt.utf8 = isUtf8; 

  return qio_regexp_create_compile(str, str_len, &opt, compiled);
}

void qio_regexp_retain(const qio_regexp_t* compiled)
{
  re_t* re = (re_t*) compiled->regexp;
  //fprintf(stdout, "Retain %p\n", re);
  DO_RETAIN(re);
}

void qio_regexp_release(qio_regexp_t* compiled)
{
  re_t* re = (re_t*) compiled->regexp;
  //fprintf(stdout, "Release %p\n", re);
  DO_RELEASE(re, re_free);
  compiled->regexp = NULL;
}

void qio_regexp_get_options(const qio_regexp_t* regexp, qio_regexp_options_t* options)
{
  //re_t* re = (re_t*) regexp->regexp;
  //const RE2::Options& opts = re2->options();
  //re2_options_to_qio_re_options(&opts, options);
  // TODO
}

void qio_regexp_get_pattern(const qio_regexp_t* regexp, const char** pattern)
{
  re_t* re = (re_t*) regexp->regexp;
  char* buf;

  buf = qio_malloc(re->pat_len+1);
  memcpy(buf, re->pat, re->pat_len);
  buf[re->pat_len] = '\0';
  *pattern = buf;
}

int64_t qio_regexp_get_ncaptures(const qio_regexp_t* regexp)
{
  // TODO
  return 20;
}
qio_bool qio_regexp_ok(const qio_regexp_t* regexp)
{
  re_t* re = (re_t*) regexp->regexp;
  return (re->errcode == 0);
}

const char* qio_regexp_error(const qio_regexp_t* regexp)
{
  re_t* re = (re_t*) regexp->regexp;
  if (re->errcode != 0) {
    size_t buf_size = tre_regerror(re->errcode, &re->r, NULL, 0);
    char *buf = qio_calloc(buf_size+1, 1);
    tre_regerror(re->errcode, &re->r, buf, buf_size);
    return buf;
  }
  return NULL;
}

qio_bool qio_regexp_match(qio_regexp_t* regexp, const char* text, int64_t text_len, int64_t startpos, int64_t endpos, int anchor, qio_regexp_string_piece_t* submatch, int64_t nsubmatch)
{
  re_t* re = (re_t*) regexp->regexp;
  int rc;
  MAYBE_STACK_SPACE(regmatch_t, onstack);
  regmatch_t* matchPtr;
  int64_t use_captures = nsubmatch;
  qio_bool found = false;

  // TODO anchor
  /*
  if( anchor == QIO_REGEXP_ANCHOR_UNANCHORED ) ranchor = RE2::UNANCHORED;
  else if( anchor == QIO_REGEXP_ANCHOR_START ) ranchor = RE2::ANCHOR_START;
  else if( anchor == QIO_REGEXP_ANCHOR_BOTH ) ranchor = RE2::ANCHOR_BOTH;
  */

  if (startpos < 0 || startpos >= text_len)
    startpos = 0;
  if (endpos < 0 || endpos > text_len)
    endpos = text_len;

  if( use_captures > SIZE_MAX || use_captures < 0 )
    use_captures = 0;

  MAYBE_STACK_ALLOC(regmatch_t, use_captures, matchPtr, onstack);
  memset(matchPtr, 0, sizeof(regmatch_t)*use_captures);


  rc = tre_regnexec(&re->r, &text[startpos], endpos - startpos,
                    use_captures, matchPtr, 0);

  found = (rc == REG_OK);

  // Now set submatch based on StringPieces
  for( int64_t i = 0; i < nsubmatch; i++ ) {
    if( !found ||
        matchPtr[i].rm_so < 0 ||
        matchPtr[i].rm_eo < 0 ||
        i >= use_captures) {
      submatch[i].offset = -1;
      submatch[i].len = 0;
    } else {
      submatch[i].offset = startpos + matchPtr[i].rm_so;
      submatch[i].len = matchPtr[i].rm_eo - matchPtr[i].rm_so;
    }
  }

  MAYBE_STACK_FREE(matchPtr, onstack);

  return found;
}

int64_t qio_regexp_replace(qio_regexp_t* regexp, const char* repl, int64_t repl_len, const char* str, int64_t str_len, int64_t startpos, int64_t endpos, qio_bool global, const char** str_out, int64_t* len_out)
{
  /*
  // This could make fewer copies of everything...
  // ... but it will work for the moment and this is the
  //     expedient way.
  StringPiece rewrite(repl, repl_len);
  std::string s(str, str_len);
  RE2* re = (RE2*) regexp->regexp;
  int64_t ret = 0;
  char* output = NULL;
  if( global ) {
    ret = RE2::GlobalReplace(&s, *re, rewrite);
  } else {
    if( RE2::Replace(&s, *re, rewrite) ) {
      ret = 1;
    } else {
      ret = 0;
    }
  }
  output = (char*) qio_malloc(s.length()+1);
  memcpy(output, s.data(), s.length());
  output[s.length()] = '\0';
  *str_out = output;
  *len_out = s.length();
  return ret;
  */
  // TODO;

  return -1;
}

struct tre_get_ctx {
  qio_channel_t* ch;
  int64_t end_offset;
};

static
int tre_get_next_char(tre_char_t* c, unsigned int* pos_add, void* context)
{
  struct tre_get_ctx* ctx = (struct tre_get_ctx*) context;
  qio_channel_t* ch = ctx->ch;
  int b;
  b = qio_channel_read_byte(false, ch);

  // TODO -- when can we discard?
  // TODO -- specifying the bounds on the channel?
  if (b >= 0) {
    *c = b;
    *pos_add = 1;
    return 0;
  } else {
    *c = 0;
    *pos_add = 0;
    return -1;
  }
}

qioerr qio_regexp_channel_match(const qio_regexp_t* regexp, const int threadsafe, struct qio_channel_s* ch, int64_t maxlen, int anchor, qio_bool can_discard, qio_bool keep_unmatched, qio_bool keep_whole_pattern, qio_regexp_string_piece_t* captures, int64_t ncaptures)
{
  re_t* re = (re_t*) regexp->regexp;
  int rc;
  MAYBE_STACK_SPACE(regmatch_t, onstack);
  regmatch_t* matchPtr;
  qioerr err;
  int64_t need;
  int64_t start_offset, offset, end_offset; 
  int64_t end;
  int64_t match_start = -1;
  int64_t match_len = 0;
  qio_bool found = false;
  int64_t use_captures = ncaptures;
  struct tre_get_ctx ctx = {NULL};
  tre_str_source src = {NULL};


  // TODO anchor
  /*
  if( anchor == QIO_REGEXP_ANCHOR_UNANCHORED ) ranchor = RE2::UNANCHORED;
  else if( anchor == QIO_REGEXP_ANCHOR_START ) ranchor = RE2::ANCHOR_START;
  else if( anchor == QIO_REGEXP_ANCHOR_BOTH ) ranchor = RE2::ANCHOR_BOTH;
  */

  // make sure use_captures is at least 1 
  if( use_captures > SIZE_MAX || use_captures <= 0 )
    use_captures = 1;

  if( threadsafe ) {
    err = qio_lock(&ch->lock);
    if( err ) {
      return err;
    }
  }

  start_offset = offset = qio_channel_offset_unlocked(ch);
  end_offset = qio_channel_end_offset_unlocked(ch);

  end = end_offset;
  if( maxlen != INT64_MAX ) {
    if( end_offset - start_offset > maxlen ) end = start_offset + maxlen;
  }


  if( ! qio_channel_has_mark_unlocked(ch) ) {
    // Should always have a mark when calling this function.
    QIO_GET_CONSTANT_ERROR(err, EINVAL, "missing mark");
    goto markerror;
  }

  // Require at least 1 byte and at most 1024 bytes.
  //need = re->min_match_length_bytes(); TODO
  need = 1;
  err = qio_channel_require_read(false, ch, need);
  if( qio_err_to_int(err) == EEOF ) err = 0; // ignore EOF
  if( err ) goto error;

  MAYBE_STACK_ALLOC(regmatch_t, use_captures, matchPtr, onstack);
  memset(matchPtr, 0, sizeof(regmatch_t)*use_captures);

  ctx.ch = ch;
  ctx.end_offset = end;

  src.get_next_char = tre_get_next_char;
  src.rewind = NULL;
  src.compare = NULL;
  src.context = &ctx;

  // TODO flags
  rc = tre_reguexec(&re->r, &src, use_captures, matchPtr, 0);

  found = (rc == REG_OK);

  // Now set submatch based on StringPieces
  for( int64_t i = 0; i < ncaptures; i++ ) {
    if( !found ||
        matchPtr[i].rm_so < 0 ||
        matchPtr[i].rm_eo < 0 ||
        i >= use_captures) {
      captures[i].offset = -1;
      captures[i].len = 0;
    } else {
      captures[i].offset = start_offset + matchPtr[i].rm_so;
      captures[i].len = matchPtr[i].rm_eo - matchPtr[i].rm_so;
    }
  }

  // Grab the entire match for use below.
  match_start = start_offset + matchPtr[0].rm_so;
  match_len = matchPtr[0].rm_eo;

  MAYBE_STACK_FREE(matchPtr, onstack);

error:

  // Get channel errors from within MatchSpecial1/qio_channel_read_byte 
  if( qio_err_to_int(err) == EEOF ) err = 0; // ignore EOF
  if( ! err ) err = qio_channel_error(ch);
  if( qio_err_to_int(err) == EEOF ) err = 0; // ignore EOF

  end_offset = qio_channel_offset_unlocked(ch);
  qio_channel_revert_unlocked(ch);
  offset = qio_channel_offset_unlocked(ch);
  qio_channel_mark(false, ch);

  // Adjust the channel position
  if( found ) {
    // If there was a match, put it after the match.
    end_offset = match_start + match_len;
    qio_channel_advance(false, ch, end_offset - offset);
  } else {
    if( keep_unmatched ) {
      qio_channel_advance(false, ch, start_offset - offset);
    } else {
      qio_channel_advance(false, ch, end_offset - offset);
    }
  }

markerror:
  if( threadsafe ) {
    qio_unlock(&ch->lock);
  }

  if( err == 0 && ! found ) QIO_GET_CONSTANT_ERROR(err, EFORMAT, "no match");

  return err;
}


