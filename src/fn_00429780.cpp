#include <xmmintrin.h>
struct Own_429780 { int fn_00429780(void); };

int Own_429780::fn_00429780(void)
{
    int ecx = (int)this;
    int eax;
    __m128 xmm0;
    xmm0 = _mm_load_ss((const float*)(0x7db234));
    eax = ecx;
    _mm_store_ss((float*)((eax) + 0x180), xmm0);
    xmm0 = _mm_load_ss((const float*)(0xd6f6e8));
    _mm_store_ss((float*)((eax) + 0x360), xmm0);
    xmm0 = _mm_load_ss((const float*)(0xd6f6e0));
    _mm_store_ss((float*)((eax) + 0x364), xmm0);
    xmm0 = _mm_load_ss((const float*)(0x7289d4));
    _mm_store_ss((float*)((eax) + 0x368), xmm0);
    xmm0 = _mm_load_ss((const float*)(0x80a8b0));
    _mm_store_ss((float*)((eax) + 0x370), xmm0);
    xmm0 = _mm_load_ss((const float*)(0x728bb4));
    _mm_store_ss((float*)((eax) + 0x374), xmm0);
    xmm0 = _mm_setzero_ps();
    _mm_store_ss((float*)((eax) + 0x37c), xmm0);
    *(int*)((eax) + 0x380) = 0;
    _mm_store_ss((float*)((eax) + 0x388), xmm0);
    _mm_store_ss((float*)((eax) + 0x38c), xmm0);
    _mm_store_ss((float*)((eax) + 0x390), xmm0);
    return eax;
}
