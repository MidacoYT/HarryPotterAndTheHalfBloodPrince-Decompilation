#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__cdecl sub_6E7161(_DWORD *a1, _DWORD *a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // edx

  *a2 = 0;
  result = a1;
  a2[1] = a1[1];
  v3 = (_DWORD *)a1[1];
  if ( v3 )
    *v3 = a2;
  else
    *a1 = a2;
  ++a1[2];
  a1[1] = a2;
  return result;
}
