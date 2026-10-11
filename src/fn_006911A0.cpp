#include <xmmintrin.h>

class C_fn_006911A0 {
public:
  __m128 * method(__m128 * a2, __m128 * a3);
};

__m128 * C_fn_006911A0::method(__m128 * a2, __m128 * a3)
{
  __m128 * this_ = (__m128 *)this;
  __m128 *result; // eax
  __m128 v4; // xmm1
  __m128 v5; // xmm0
  __m128 v6; // xmm0

  result = a3;
  v4 = _mm_mul_ps(*a2, *this_);
  v5 = _mm_add_ps(_mm_add_ps(_mm_shuffle_ps(v4, v4, 2), _mm_shuffle_ps(v4, v4, 1)), v4);
  v6 = _mm_shuffle_ps(v5, v5, 0);
  a3[1] = v6;
  *a3 = v6;
  return result;
}
