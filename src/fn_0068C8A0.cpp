#include <xmmintrin.h>
struct Own_68C8A0 { int fn_0068C8A0(int arg0); };

int Own_68C8A0::fn_0068C8A0(int arg0)
{
    int ecx = (int)this;
    int eax, edx;
    float __fp_68C91D;
    __m128 xmm0;
    /* own-declaration: float __fp_68C91D; */
    eax = ecx;
    ecx = *(int*)((int)&arg0);
    xmm0 = _mm_load_ps((const float*)(ecx));
    _mm_store_ps((float*)(eax), xmm0);
    xmm0 = _mm_load_ps((const float*)((ecx) + 0x10));
    _mm_store_ps((float*)((eax) + 0x10), xmm0);
    xmm0 = _mm_load_ps((const float*)((ecx) + 0x20));
    _mm_store_ps((float*)((eax) + 0x20), xmm0);
    xmm0 = _mm_load_ps((const float*)((ecx) + 0x30));
    _mm_store_ps((float*)((eax) + 0x30), xmm0);
    edx = *(int*)((ecx) + 0x40);
    *(int*)((eax) + 0x40) = edx;
    edx = *(int*)((ecx) + 0x44);
    *(int*)((eax) + 0x44) = edx;
    edx = *(int*)((ecx) + 0x44);
    *(int*)((eax) + 0x44) = edx;
    edx = *(int*)((ecx) + 0x44);
    *(int*)((eax) + 0x44) = edx;
    edx = *(int*)((ecx) + 0x44);
    *(int*)((eax) + 0x44) = edx;
    edx = *(int*)((ecx) + 0x48);
    *(int*)((eax) + 0x48) = edx;
    edx = *(int*)((ecx) + 0x4c);
    *(int*)((eax) + 0x4c) = edx;
    edx = *(int*)((ecx) + 0x44);
    *(int*)((eax) + 0x44) = edx;
    edx = *(int*)((ecx) + 0x48);
    *(int*)((eax) + 0x48) = edx;
    edx = *(int*)((ecx) + 0x4c);
    *(int*)((eax) + 0x4c) = edx;
    edx = *(int*)((ecx) + 0x44);
    *(int*)((eax) + 0x44) = edx;
    edx = *(int*)((ecx) + 0x48);
    *(int*)((eax) + 0x48) = edx;
    edx = *(int*)((ecx) + 0x44);
    *(int*)((eax) + 0x44) = edx;
    edx = *(int*)((ecx) + 0x48);
    *(int*)((eax) + 0x48) = edx;
    __fp_68C91D = *(float*)((ecx) + 0x50);
    *(float*)((eax) + 0x50) = (float)(__fp_68C91D);
    edx = *(int*)((ecx) + 0x54);
    *(int*)((eax) + 0x54) = edx;
    edx = *(int*)((ecx) + 0x58);
    *(int*)((eax) + 0x58) = edx;
    ecx = *(int*)((ecx) + 0x5c);
    *(int*)((eax) + 0x5c) = ecx;
    return eax;
}
