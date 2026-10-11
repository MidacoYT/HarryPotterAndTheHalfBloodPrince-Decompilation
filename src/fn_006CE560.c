#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__cdecl sub_6CE560(_DWORD *a1, unsigned __int8 *a2)
{
  _DWORD *result; // eax

  result = a1;
  a1[4] = 0;
  *a1 = 0;
  a1[1] = 255;
  a1[3] = 8;
  a1[5] = a2;
  a1[2] = a2[3] + ((a2[2] + ((a2[1] + (*a2 << 8)) << 8)) << 8);
  a1[4] = 4;
  return result;
}
