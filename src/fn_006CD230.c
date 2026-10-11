#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl sub_6CD230(unsigned __int8 *a1, unsigned int *a2)
{
  int v2; // esi
  unsigned int v3; // edx
  unsigned int v4; // edi
  unsigned int v5; // esi
  unsigned int v6; // esi
  unsigned int v7; // edx
  unsigned int v8; // edx
  unsigned int v9; // esi
  unsigned int v10; // esi
  int result; // eax

  a2[11] = (a1[1] * (unsigned int)*a1) >> 8;
  *a2 = (*a1 * (255 - (unsigned int)a1[1])) >> 8;
  v2 = 255 - *a1;
  a2[1] = (v2 * (unsigned int)a1[2]) >> 8;
  v3 = (v2 * (255 - (unsigned int)a1[2])) >> 8;
  v4 = (v3 * a1[3]) >> 8;
  a2[2] = (v4 * a1[4]) >> 8;
  v5 = (v4 * (255 - a1[4])) >> 8;
  a2[3] = (v5 * a1[5]) >> 8;
  a2[4] = (v5 * (255 - a1[5])) >> 8;
  v6 = (v3 * (255 - a1[3])) >> 8;
  v7 = (v6 * a1[6]) >> 8;
  a2[5] = (v7 * a1[7]) >> 8;
  a2[6] = (v7 * (255 - a1[7])) >> 8;
  v8 = (v6 * (255 - a1[6])) >> 8;
  v9 = (v8 * a1[8]) >> 8;
  a2[7] = (v9 * a1[9]) >> 8;
  a2[8] = (v9 * (255 - a1[9])) >> 8;
  v10 = (v8 * (255 - a1[8])) >> 8;
  a2[9] = (v10 * a1[10]) >> 8;
  result = a1[10];
  a2[10] = (v10 * (255 - result)) >> 8;
  return result;
}
