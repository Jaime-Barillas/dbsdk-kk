/*---------------------------------------------------------------------------
  Copyright 2020-2023, Microsoft Research, Daan Leijen.

  This is free software; you can redistribute it and/or modify it under the
  terms of the Apache License, Version 2.0. A copy of the License can be
  found in the LICENSE file at the root of this distribution.
---------------------------------------------------------------------------*/
#include "kklib.h"

/* ----------------------------------------------------------
  kk_bits_digits
-------------------------------------------------------------*/

static const kk_uintx_t powers_of_10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
#if (KK_INTX_SIZE > 4)
  , KK_UX(10000000000), KK_UX(100000000000), KK_UX(1000000000000), KK_UX(10000000000000), KK_UX(100000000000000)
  , KK_UX(1000000000000000), KK_UX(10000000000000000), KK_UX(100000000000000000), KK_UX(1000000000000000000)
  , KK_UX(10000000000000000000), KK_UX(10000000000000000000)
#endif
};

int kk_bits_digits32(uint32_t u) {
  static const int8_t guess[33] = {
    1, 0, 0, 0, 1, 1, 1, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
    6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
    9, 9, 9
  };
  const int count = guess[32 - kk_bits_clz32(u)]; // = 1 + (KU32(9)*(31 - kk_bits_clz32(u)) >> 5);
  return (count + (u >= powers_of_10[count] ? 1 : 0));
}

int kk_bits_digits64(uint64_t u) {
  static const int8_t guess[65] = {
    1, 0, 0, 0, 1, 1, 1, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
    6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
    9, 9, 9, 9,10,10,10,11,11,11,
   12,12,12,12,13,13,13,14,14,14,
   15,15,15,15,16,16,16,17,17,17,
   18,18,18,18,19
  };
  const int count = guess[64 - kk_bits_clz64(u)];  // = 1 + (KU64(1233)*(63 - kk_bits_clz64(u)) >> 12);
  return (count + (u >= powers_of_10[count] ? 1 : 0));
}

/* ----------------------------------------------------------
  generic ctz, clz
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_CTZ_CLZ32
int kk_bits_ctz32(uint32_t x) {
  // de Bruijn multiplication, see <http://supertech.csail.mit.edu/papers/debruijn.pdf>
  static const int8_t debruijn[32] = {
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
  };
  if (x == 0) return 32;
  x = kk_bits_only_keep_lsb32(x);
  return debruijn[(uint32_t)(x * KK_U32(0x077CB531)) >> 27];
}

int kk_bits_clz32(uint32_t x) {
  // de Bruijn multiplication, see <http://supertech.csail.mit.edu/papers/debruijn.pdf>
  static const int8_t debruijn[32] = {
    31, 22, 30, 21, 18, 10, 29, 2, 20, 17, 15, 13, 9, 6, 28, 1,
    23, 19, 11, 3, 16, 14, 7, 24, 12, 4, 8, 25, 5, 26, 27, 0
  };
  if (x==0) return 32;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return debruijn[(uint32_t)(x * KK_U32(0x07C4ACDD)) >> 27];
}
#endif


/* ----------------------------------------------------------
  or-combine
-------------------------------------------------------------*/
#define kk_mask_even_pairs32     KK_U32(0x33333333)
#define kk_mask_even_nibbles32   KK_U32(0x0F0F0F0F)
#define kk_mask_even_pairs64     KK_U64(0x3333333333333333)
#define kk_mask_even_nibbles64   KK_U64(0x0F0F0F0F0F0F0F0F)

#if !KK_BITS_HAS_FAST_ORC32
uint32_t kk_bits_orc32(uint32_t x) {
  // set high bit in each byte to `or` of the bits in the byte
  x |= ((x & kk_mask_even_nibbles32) << 4);
  x |= ((x & kk_mask_even_pairs32)   << 2);
  x |= ((x & kk_mask_even_bits32)    << 1);
  // distribute the high bit back
  x &= kk_mask_bytes_hi_bit32;
  x |= (x >> 1);
  x |= (x >> 2);
  x |= (x >> 4);
  return x;
}
#endif

#if !KK_BITS_HAS_FAST_ORC64
uint64_t kk_bits_orc64(uint64_t x) {
  // set high bit in each byte to `or` of the bits in the byte
  x |= ((x & kk_mask_even_nibbles64) << 4);
  x |= ((x & kk_mask_even_pairs64)   << 2);
  x |= ((x & kk_mask_even_bits64)    << 1);
  // distribute the high bit back
  x &= kk_mask_bytes_hi_bit64;
  x |= (x >> 1);
  x |= (x >> 2);
  x |= (x >> 4);
  return x;
}
#endif

/* ----------------------------------------------------------
  has byte?, byte sum
-------------------------------------------------------------*/

// is there any byte in `x` equal to `n`?
bool kk_bits_has_byte32(uint32_t x, uint8_t n) {
  uint32_t y = n;
  y |= (y << 8);
  y |= (y << 16);
  x ^= y;
  return kk_bits_has_zero_byte32(x);
}

// is there any byte in `x` equal to `n`?
bool kk_bits_has_byte64(uint64_t x, uint8_t n) {
  uint64_t y = n;
  y |= (y << 8);
  y |= (y << 16);
  y |= (y << 32);
  x ^= y;
  return kk_bits_has_zero_byte64(x);
}


// sum of all the bytes in `x` if it is guaranteed that the sum < 256!
uint8_t kk_bits_byte_sum32(uint32_t x) {
  // perform `x * kk_mask_bytes_lo_bit`: the highest byte contains the sum of all bytes.
  // note: clang will compile to either shift/adds or a multiply depending on the target
  x += (x << 8);
  x += (x << 16);
  return (x >> 24);
}

// sum of all the bytes in `x` if it is guaranteed that the sum < 256!
uint8_t kk_bits_byte_sum64(uint64_t x) {
  x += (x << 8);
  x += (x << 16);
  x += (x << 32);
  return (x >> 56);
}


/* ----------------------------------------------------------
  generic popcount
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_POPCOUNT32
int kk_bits_popcount32(uint32_t x) {
  // first count each 2-bit group `a`, where: a==0b00 -> 00, a==0b01 -> 01, a==0b10 -> 01, a==0b11 -> 10
  // in other words, `a - (a>>1)`; to do this in parallel, we need to mask to prevent spilling a bit pair
  // into the lower bit-pair:
  x = x - ((x >> 1) & kk_mask_even_bits32);
  // add the 2-bit pair results
  x = (x & kk_mask_even_pairs32) + ((x >> 2) & kk_mask_even_pairs32);
  // add the 4-bit nibble results
  x = (x + (x >> 4)) & kk_mask_even_nibbles32;
  // each byte now has a count of its bits, we can sum them now:
  return kk_bits_byte_sum32(x);
}
#endif

#if !KK_BITS_HAS_FAST_POPCOUNT64
int kk_bits_popcount64(uint64_t x) {
  x = x - ((x >> 1) & kk_mask_even_bits64);
  x = (x & kk_mask_even_pairs64) + ((x >> 2) & kk_mask_even_pairs64);
  x = (x + (x >> 4)) & kk_mask_even_nibbles64;
  return kk_bits_byte_sum64(x);
}
#endif


/* ----------------------------------------------------------
  parity
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_PARITY32
bool kk_bits_parity32(uint32_t x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x &= 0x0F;
  return (((0x6996 >> x) & 1) == 0);  // 0x6996 = 0b0110100110010110  == "mini" 16 bit lookup table with a bit set if the value has non-even parity
}
#endif


/* ----------------------------------------------------------
  Bit reverse
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_BITREVERSE32
uint32_t kk_bits_reverse32(uint32_t x) {
  // from: http://graphics.stanford.edu/~seander/bithacks.html#ReverseParallel
  x = ((x >> 1) & kk_mask_even_bits32) | ((x & kk_mask_even_bits32) << 1); // swap odd and even bits
  x = ((x >> 2) & kk_mask_even_pairs32) | ((x & kk_mask_even_pairs32) << 2); // swap 2-bit pairs
  x = ((x >> 4) & kk_mask_even_nibbles32) | ((x & kk_mask_even_nibbles32) << 4); // swap 4-bit nibbles
  return kk_bits_bswap32(x);
}
#endif

#if !KK_BITS_HAS_FAST_BITREVERSE64
uint64_t kk_bits_reverse64(uint64_t x) {
  x = ((x >> 1) & kk_mask_even_bits64) | ((x & kk_mask_even_bits64) << 1); // swap odd and even bits
  x = ((x >> 2) & kk_mask_even_pairs64) | ((x & kk_mask_even_pairs64) << 2); // swap 2-bit pairs
  x = ((x >> 4) & kk_mask_even_nibbles64) | ((x & kk_mask_even_nibbles64) << 4); // swap 4-bit nibbles
  return kk_bits_bswap64(x);
}
#endif


/* ----------------------------------------------------------
  wide multiplies
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_MUL64_WIDE

/* multiply to 64-bit integers `x` and `y` using 32x32 to 64-bit multiplications:

                    yhi : ylo
                    xhi : xlo  *
        ---------------------
                    ahi : alo   // xlo * ylo
              bhi : blo         // xlo * yhi
              chi : clo         // xhi * ylo
        dhi : dlo               // xhi * xhi
             carry              // (ahi + blo + clo) >> 32
        ---------------------+
           hi     :    lo
*/

#define kk_split32(x)   const uint64_t x##lo = (uint32_t)(x); const uint64_t x##hi = (x)>>32;

uint64_t kk_umul64_wide(uint64_t x, uint64_t y, uint64_t* hi) {
  kk_split32(x); kk_split32(y);
  uint64_t a = xlo * ylo;
  uint64_t b = xhi * ylo;
  uint64_t c = xlo * yhi;
  uint64_t d = xhi * yhi;

  kk_split32(a); kk_split32(b); kk_split32(c); kk_unused(alo);
  uint64_t carry = (ahi + blo + clo) >> 32;
  uint64_t lo = a + (blo << 32) + (clo << 32);
  *hi = carry + bhi + chi + d;
  return lo;
}

uint64_t kk_imul64_wide(int64_t x, int64_t y, int64_t* hi) {
  int64_t  z;
  uint64_t lo = kk_umul64_wide((uint64_t)x, (uint64_t)y, (uint64_t*)&z);
  if (x < 0) { z -= y; }
  if (y < 0) { z -= x; }
  *hi = z;
  return lo;
}
#endif


/* ----------------------------------------------------------
  generic parallel bit extract / deposit
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_SCATTER_GATHER32
uint32_t kk_bits_scatter32(uint32_t x, uint32_t mask) {
  uint32_t y = 0;
  while (mask != 0) {
    int shift = kk_bits_ctz32(mask);   // find lsb
    y |= ((x & 1) << shift);
    x >>= 1;
    mask = kk_bits_clear_lsb32(mask);  // clear lsb
  }
  return y;
}

uint32_t kk_bits_gather32(uint32_t x, uint32_t mask) {
  uint32_t y = 0;
  while(mask != 0) {
    int shift = kk_bits_clz32(mask); // find msb
    x <<= shift;
    mask <<= shift;
    y = (y << 1) | (x >> 31);  // shift in one bit
    mask = (mask << 1) >> 1;   // clear mask msb
  }
  return y;
}
#endif

#if !KK_BITS_HAS_FAST_SCATTER_GATHER64
uint64_t kk_bits_scatter64(uint64_t x, uint64_t mask) {
  uint64_t y = 0;
  while (mask != 0) {
    int shift = kk_bits_ctz64(mask);   // find lsb
    y |= ((x & 1) << shift);
    x >>= 1;
    mask = kk_bits_clear_lsb64(mask);  // clear lsb
  }
  return y;
}

uint64_t kk_bits_gather64(uint64_t x, uint64_t mask) {
  uint64_t y = 0;
  while(mask != 0) {
    int shift = kk_bits_clz64(mask); // find msb
    x <<= shift;
    mask <<= shift;
    y = (y << 1) | (x >> 63);  // shift in one bit
    mask = (mask << 1) >> 1;   // clear mask msb
  }
  return y;
}
#endif


/* ----------------------------------------------------------
  carry-less multiplication

                  1 0 1 0 0 0 1 0 = x
                  1 0 0 1 0 1 1 0 = y
   -------------------------------
                1 0 1 0 0 0 1 0|0   shift by 1
              1 0 1 0 0 0 1 0|0 0   shift by 2
          1 0 1 0 0 0 1 0|0 0 0 0   shift by 4
    1 0 1 0 0 0 1 0|0 0 0 0 0 0 0   shift by 7
   ------------------------------- ^
    1 0 1 1 0 0 0 1 1 1 0 1 1 0 0
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_CLMUL32
// multiply with the least-significant bit; as this is a power of 2,
// the result won't produce a carry so we can xor safely.
uint32_t kk_clmul32(uint32_t x, uint32_t y) {
  uint32_t z = 0;
	while (y!=0) {
    z ^= x << kk_bits_ctz32(y);
    y = kk_bits_clear_lsb32(y);
  }
	return z;
}
uint32_t kk_clmul32_wide(uint32_t x, uint32_t y, uint32_t* hi) {
  uint64_t z = kk_clmul64(x,y);
  *hi = (uint32_t)(z >> 32);
  return (uint32_t)z;
}
#endif

#if !KK_BITS_HAS_FAST_CLMUL64
uint64_t kk_clmul64(uint64_t x, uint64_t y) {
  uint64_t z = 0;
	while (y!=0) {
    z ^= x << kk_bits_ctz64(y);
    y = kk_bits_clear_lsb64(y);
  };
	return z;
}

uint64_t kk_clmul64_wide(uint64_t x, uint64_t y, uint64_t* hi) {
  uint64_t zlo = 0;
  uint64_t zhi = 0;
  int shift;
  while (y != 0) {
    shift = kk_bits_ctz64(y);
    zlo ^= x << shift;
    zhi ^= x >> (64 - shift);
    y = kk_bits_clear_lsb64(y);
  }
  *hi = zhi;
  return zlo;
}
#endif

#if !KK_BITS_HAS_FAST_CLMULR32
uint32_t kk_clmulr32(uint32_t x, uint32_t y) {
  uint32_t z = 0;
	while (y!=0) {
    z ^= x >> (32 - kk_bits_ctz32(y) - 1);
    y = kk_bits_clear_lsb32(y);
  };
	return z;
}
#endif

#if !KK_BITS_HAS_FAST_CLMULR64
uint64_t kk_clmulr64(uint64_t x, uint64_t y) {
  uint64_t z = 0;
	while (y!=0) {
    z ^= x >> (64 - kk_bits_ctz64(y) - 1);
    y = kk_bits_clear_lsb64(y);
  };
	return z;
}
#endif


/* ----------------------------------------------------------
  xperm
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_XPERM32
uint32_t kk_bits_xperm32(uint32_t x, uint32_t indices) {
  uint32_t r = 0;
  for (int i = 0; i < 32; i += 8) {
    uint32_t idx = (indices >> i) & 0x03;
    r |= ((x >> (8*idx)) & 0xFF) << i;
  }
  return r;
}

uint32_t kk_bits_xpermn32(uint32_t x, uint32_t indices) {
  uint32_t r = 0;
  for (int i = 0; i < 32; i += 4) {
    uint32_t idx = (indices >> i) & 0x07;
    r |= ((x >> (4*idx)) & 0x0F) << i;
  }
  return r;
}
#endif

#if !KK_BITS_HAS_FAST_XPERM64
uint64_t kk_bits_xperm64(uint64_t x, uint64_t indices) {
  uint64_t r = 0;
  for (int i = 0; i < 64; i += 8) {
    uint64_t idx = (indices >> i) & 0x07;
    r |= ((x >> (8*idx)) & 0xFF) << i;
  }
  return r;
}

uint64_t kk_bits_xpermn64(uint64_t x, uint64_t indices) {
  uint64_t r = 0;
  for (int i = 0; i < 64; i += 4) {
    uint32_t idx = (indices >> i) & 0x0F;
    r |= ((x >> (4*idx)) & 0x0F) << i;
  }
  return r;
}

#endif


/* ----------------------------------------------------------
  zip/unzip
-------------------------------------------------------------*/

#if !KK_BITS_HAS_FAST_ZIP32
// scatter bits to even positions
static inline uint32_t kk_bits_scatter_even32( uint32_t x ) {
  x = (x | (x << 8 )) & KK_U32(0x00FF00FF);
  x = (x | (x << 4 )) & kk_mask_even_nibbles32;
  x = (x | (x << 2 )) & kk_mask_even_pairs32;
  x = (x | (x << 1 )) & kk_mask_even_bits32;
  return x;
}

uint32_t kk_bits_zip32(uint32_t x) {
  return ((kk_bits_scatter_even32(x >> 16) << 1) | kk_bits_scatter_even32(x & 0xFFFF));
}
#endif

#if !KK_BITS_HAS_FAST_UNZIP32
// gather even bits
static inline uint32_t kk_bits_gather_even32(uint32_t x) {
  x = x & kk_mask_even_bits32;
  x = (x | (x >> 1 )) & kk_mask_even_pairs32;
  x = (x | (x >> 2 )) & kk_mask_even_nibbles32;
  x = (x | (x >> 4 )) & KK_U32(0x00FF00FF);
  x = (x | (x >> 8 )) & KK_U32(0x0000FFFF);
  return x;
}

uint32_t kk_bits_unzip32(uint32_t x) {
  return ((kk_bits_gather_even32(x >> 1) << 16) | kk_bits_gather_even32(x));
}
#endif

#if !KK_BITS_HAS_FAST_ZIP64
static inline uint64_t kk_bits_scatter_even64( uint64_t x ) {
  x = (x | (x << 16)) & KK_U64(0x0000FFFF0000FFFF);
  x = (x | (x << 8 )) & KK_U64(0x00FF00FF00FF00FF);
  x = (x | (x << 4 )) & kk_mask_even_nibbles64;
  x = (x | (x << 2 )) & kk_mask_even_pairs64;
  x = (x | (x << 1 )) & kk_mask_even_bits64;
  return x;
}
uint64_t kk_bits_zip64(uint64_t x) {
  return ((kk_bits_scatter_even64(x>>32) << 1) | kk_bits_scatter_even64(x & KK_U64(0xFFFFFFFF)));
}
#endif

#if !KK_BITS_HAS_FAST_UNZIP64
static inline uint64_t kk_bits_gather_even64(uint64_t x) {
  x = x & kk_mask_even_bits64;
  x = (x | (x >> 1 )) & kk_mask_even_pairs64;
  x = (x | (x >> 2 )) & kk_mask_even_nibbles64;
  x = (x | (x >> 4 )) & KK_U64(0x00FF00FF00FF00FF);
  x = (x | (x >> 8 )) & KK_U64(0x0000FFFF0000FFFF);
  x = (x | (x >> 16)) & KK_U64(0x00000000FFFFFFFF);
  return x;
}
uint64_t kk_bits_unzip64(uint64_t x) {
  return ((kk_bits_gather_even64(x>>1) << 32) | kk_bits_gather_even64(x));
}
#endif

