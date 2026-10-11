#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern float *__cdecl sub_6EAE2E(float *a1, int a2);
int __cdecl sub_6E7FA4(int a1, int *a2)
{
  int v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]
  float v5; // [esp+14h] [ebp+Ch]

  v3 = a2[1] >> 7;
  v4 = *a2 >> 7;
  v5 = (float)(a2[2] >> 8);
  *(float *)(a1 + 80) = (double)v4 / v5;
  *(float *)(a1 + 84) = (double)v3 / v5;
  return sub_6EAE2E(a1 + 28, 4);
}
