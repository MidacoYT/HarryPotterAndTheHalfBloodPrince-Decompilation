#include <xmmintrin.h>
__declspec(noinline) int fn_005B7C00(int eax)
{
    int ecx;
    __m128 xmm0;
eax = *(int*)((eax) + 0xa70);
if (((unsigned int)(eax)) == ((unsigned int)(0))) goto L_5B7C75;
ecx = *(int*)(0x89d914);
if (((unsigned int)(ecx)) != ((unsigned int)(*(int*)((eax) + 0x50)))) goto L_5B7C75;
xmm0 = _mm_load_ss((const float*)(0x80a8f4));
_mm_store_ss((float*)((eax) + 0x8100), xmm0);
xmm0 = _mm_load_ss((const float*)(0x7db234));
_mm_store_ss((float*)((eax) + 0x8104), xmm0);
xmm0 = _mm_load_ss((const float*)(0x83b230));
_mm_store_ss((float*)((eax) + 0x80f8), xmm0);
xmm0 = _mm_load_ss((const float*)(0x83b234));
_mm_store_ss((float*)((eax) + 0x80fc), xmm0);
xmm0 = _mm_load_ss((const float*)(0x831c24));
_mm_store_ss((float*)((eax) + 0x80f0), xmm0);
xmm0 = _mm_load_ss((const float*)(0x83b254));
_mm_store_ss((float*)((eax) + 0x80f4), xmm0);
L_5B7C75:;
return eax;
}
