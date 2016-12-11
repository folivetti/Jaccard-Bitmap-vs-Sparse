#include <stdint.h>
#include <immintrin.h>

/* print a 256 bits number */
void print_m256(__m256i m);

/* set bit k of a 256 bit vector */
inline void setbit_256( __m256i * x, int k );

/* count number of 1s in 256 bit number */
inline int popcount_256( const uint64_t * x );

/* calculates jaccard similarity from 2 vectors of 256 bit numbers */
double _mm256_jaccard( __m256i * d1, __m256i * d2, int size );

