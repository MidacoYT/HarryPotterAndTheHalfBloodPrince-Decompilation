#include <xmmintrin.h>

void __fastcall fn_00491F60(float *self, void *edx_unused, float value)
{
    __m128 vector = _mm_load_ss(&value);
    (void)edx_unused;
    vector = _mm_shuffle_ps(vector, vector, 0);
    _mm_store_ps(self, vector);
}
