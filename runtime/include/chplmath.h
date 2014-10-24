#ifndef _CHPL_MATH_H_
#define _CHPL_MATH_H_

#ifdef DEFINE_32_BIT_MATH_FNS
#define fabsf(x) (float)fabs(x)
#define cosf(x) (float)cos(x)
#define erff(x) (float)erf(x)
#define expf(x) (float)exp(x)
#define logf(x) (float)log(x)
#define sinf(x) (float)sin(x)
#define tanf(x) (float)tan(x)
#define acosf(x) (float)acos(x)
#define asinf(x) (float)asin(x)
#define atanf(x) (float)atan(x)
#define cbrtf(x) (float)cbrt(x)
#define ceilf(x) (float)ceil(x)
#define coshf(x) (float)cosh(x)
#define erfcf(x) (float)erfc(x)
#define exp2f(x) (float)exp2(x)
#define log2f(x) (float)log2(x)
#define rintf(x) (float)rint(x)
#define sinhf(x) (float)sinh(x)
#define tanhf(x) (float)tanh(x)
#define sqrtf(x) (float)sqrt(x)
#define lgammaf(x) (float)lgamma(x)
#define acoshf(x) (float)acosh(x)
#define asinhf(x) (float)asinh(x)
#define atan2f(x,y) (float)atan2(x,y)
#define atanhf(x) (float)atanh(x)
#define expm1f(x) (float)expm1(x)
#define floorf(x) (float)floor(x)
#define log10f(x) (float)log10(x)
#define log1pf(x) (float)log1p(x)
#define roundf(x) (float)round(x)
#define truncf(x) (float)trunc(x)
#define nearbyintf(x) (float)nearbyint(x)
#define tgammaf(x) (float)tgamma(x)
#endif

#ifndef __GNUC__
#ifndef __clang__
#define NEEDS_COMPAT_BUILTINS
#endif
#endif

#ifdef NEEDS_COMPAT_BUILTINS
static inline int chpl_leadz8(uint8_t x) {
  int i;
  for( i = 0; i < 8; i++ ) {
    if( x >> 7 ) break;
    x <<= 1;
  }
  return i;
}
static inline int chpl_leadz16(uint16_t x) {
  int i;
  for( i = 0; i < 16; i++ ) {
    if( x >> 15 ) break;
    x <<= 1;
  }
  return i;
}
static inline int chpl_leadz32(uint32_t x) {
  int i;
  for( i = 0; i < 32; i++ ) {
    if( x >> 31 ) break;
    x <<= 1;
  }
  return i;
}
static inline int chpl_leadz64(uint64_t x) {
  int i;
  for( i = 0; i < 64; i++ ) {
    if( x >> 63 ) break;
    x <<= 1;
  }
  return i;
}
static inline int chpl_trailz8(uint8_t x) {
  int i;
  for( i = 0; i < 8; i++ ) {
    if( x & 1 ) break;
    x >>= 1;
  }
  return i;
}
static inline int chpl_trailz16(uint16_t x) {
  int i;
  for( i = 0; i < 16; i++ ) {
    if( x & 1) break;
    x >>= 1;
  }
  return i;
}
static inline int chpl_trailz32(uint32_t x) {
  int i;
  for( i = 0; i < 32; i++ ) {
    if( x & 1 ) break;
    x >>= 1;
  }
  return i;
}
static inline int chpl_trailz64(uint64_t x) {
  int i;
  for( i = 0; i < 64; i++ ) {
    if( x & 1 ) break;
    x >>= 1;
  }
  return i;
}
/* These popcounts could be done more efficiently -- something like
// reimplementation note: one bitPop routine when numBits is a parameter
proc bitPop(i: integral) where (i.type == int(64)) || (i.type == uint(64)) {
  const u1 = 10540996613548315209:uint(64);
  const u3 = 13176245766935394011:uint(64);
  const u7 = 9349719599003471367:uint(64);
  var ii = i: uint(64);
  var tmp = ii - ((ii >> 1) & u3) - ((ii >> 2) & u1);
  return ((((tmp + (tmp >> 3)) & u7) + ((tmp >> 6) & u7)) % 511):int;
}

proc bitPop(i: integral) where (i.type == int(32)) || (i.type == uint(32)) {
  const u1 = 10540996613548315209:uint(32);
  const u3 = 13176245766935394011:uint(32);
  const u7 = 9349719599003471367:uint(32);
  var ii = i: uint(32);
  var tmp = ii - ((ii >> 1) & u3) - ((ii >> 2) & u1);
  return ((((tmp + (tmp >> 3)) & u7) + ((tmp >> 6) & u7)) % 511):int;
}

proc bitPop(i: integral) where (i.type == int(16)) || (i.type == uint(16)) {
  const u1 = 10540996613548315209:uint(16);
  const u3 = 13176245766935394011:uint(16);
  const u7 = 9349719599003471367:uint(16);
  var ii = i: uint(16);
  var tmp = ii - ((ii >> 1) & u3) - ((ii >> 2) & u1);
  return ((((tmp + (tmp >> 3)) & u7) + ((tmp >> 6) & u7)) % 511):int;
}

proc bitPop(i: integral) where (i.type == int(8)) || (i.type == uint(8)) {
  const u1 = 10540996613548315209:uint(8);
  const u3 = 13176245766935394011:uint(8);
  const u7 = 9349719599003471367:uint(8);
  var ii = i: uint(8);
  var tmp = ii - ((ii >> 1) & u3) - ((ii >> 2) & u1);
  return ((((tmp + (tmp >> 3)) & u7) + ((tmp >> 6) & u7)) % 511):int;
}
*/
static inline int chpl_popcnt8(uint8_t x) {
  int i;
  int ret = 0;
  for( i = 0; i < 8; i++ ) {
    ret += ( x & 1 );
    x >>= 1;
  }
  return ret;
}
static inline int chpl_popcnt16(uint16_t x) {
  int i;
  int ret = 0;
  for( i = 0; i < 16; i++ ) {
    ret += ( x & 1);
    x >>= 1;
  }
  return ret;
}
static inline int chpl_popcnt32(uint32_t x) {
  int i;
  int ret = 0;
  for( i = 0; i < 32; i++ ) {
    ret += ( x & 1 );
    x >>= 1;
  }
  return ret;
}
static inline int chpl_popcnt64(uint64_t x) {
  int i;
  int ret;
  for( i = 0; i < 64; i++ ) {
    ret += (x & 1);
    x >>= 1;
  }
  return ret;
}
#else
static inline int chpl_leadz8(uint8_t x) {
  return __builtin_clz((unsigned int) x) - 8*(sizeof(unsigned int)-sizeof(uint8_t));
}
static inline int chpl_leadz16(uint16_t x) {
  return __builtin_clz((unsigned int) x) - 8*(sizeof(unsigned int)-sizeof(uint16_t));
}
static inline int chpl_leadz32(uint32_t x) {
  return __builtin_clz((unsigned int) x);
}
static inline int chpl_leadz64(uint64_t x) {
  return __builtin_clzll((unsigned long long) x);
}
static inline int chpl_trailz8(uint8_t x) {
  return __builtin_ctz((unsigned int) x);
}
static inline int chpl_trailz16(uint16_t x) {
  return __builtin_ctz((unsigned int) x);
}
static inline int chpl_trailz32(uint32_t x) {
  return __builtin_ctz((unsigned int) x);
}
static inline int chpl_trailz64(uint64_t x) {
  return __builtin_ctzll((unsigned long long) x);
}
static inline int chpl_popcnt8(uint8_t x) {
  return __builtin_popcount((unsigned int)x);
}
static inline int chpl_popcnt16(uint16_t x) {
  return __builtin_popcount((unsigned int)x);
}
static inline int chpl_popcnt32(uint32_t x) {
  return __builtin_popcount((unsigned int)x);
}
static inline int chpl_popcnt64(uint64_t x) {
  return __builtin_popcountll((unsigned long long)x);
}
#endif

#undef NEEDS_COMPAT_BUILTINS

#endif
