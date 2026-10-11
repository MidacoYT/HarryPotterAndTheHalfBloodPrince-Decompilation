#include <xmmintrin.h>

void *__fastcall fn_00405250(float *self, void *edx_unused, const float *source)
{
    __m128 value = _mm_load_ss(source);
    (void)edx_unused;
    value = _mm_shuffle_ps(value, value, 0);
    _mm_store_ps(self, value);
    return self;
}
