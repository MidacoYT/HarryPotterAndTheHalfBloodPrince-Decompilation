#include <xmmintrin.h>
unsigned char __cdecl fn_004D5480(const float *a, const float *b) {
    __m128 x = _mm_load_ps(a);
    __m128 y = _mm_load_ps(b);
    return (unsigned char)((_mm_movemask_ps(_mm_cmpeq_ps(x, y)) & 7) == 7);
}
