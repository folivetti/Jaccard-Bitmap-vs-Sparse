#include <stdio.h>
#include "bitmap.h"

void print_m256(__m256i m)
{
    unsigned long long int * x = (unsigned long long int *)&m;
    printf("%Lu %Lu %Lu %Lu\n", x[3], x[2], x[1], x[0]);
}

inline void setbit_256( __m256i * x, int k )
{
  __m256i indices = _mm256_set_epi32(224,192,160,128,96,64,32,0);
  __m256i one = _mm256_set1_epi32(-1);
  one = _mm256_srli_epi32(one, 31);    // set1(0x1)


  __m256i kvec = _mm256_set1_epi32(k);  
  __m256i shiftcounts = _mm256_sub_epi32(kvec, indices);
  __m256i kbit        = _mm256_sllv_epi32(one, shiftcounts);
  *x = _mm256_or_si256(kbit, *x);                           
}

inline int popcount_256( const uint64_t * x )
{
    return _mm_popcnt_u64(x[0]) + _mm_popcnt_u64(x[1]) + _mm_popcnt_u64(x[2]) + _mm_popcnt_u64(x[3]);
}

double _mm256_jaccard( __m256i * d1, __m256i * d2, int size )
{
    int bit_union = 0, bit_intersect = 0;
    int i;
    __m256i tmp_u, tmp_i;

    for(i=0; i<size; i++) {
        tmp_i = _mm256_and_si256( d1[i], d2[i] );
        tmp_u = _mm256_or_si256( d1[i], d2[i] );
        bit_union += popcount_256( (uint64_t *) &tmp_u );
        bit_intersect += popcount_256( (uint64_t *) &tmp_i );
    }

    if (!bit_union) return 0.0;

    return (double)bit_intersect/(double)bit_union;
}
