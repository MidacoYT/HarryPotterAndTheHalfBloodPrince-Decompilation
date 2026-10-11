#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__cdecl sub_6E713D(_DWORD *a1, _DWORD *a2)
{
  _DWORD *result; // eax
  int v3; // edx

  result = a1;
  v3 = *a1;
  a2[1] = 0;
  *a2 = v3;
  if ( *a1 )
    *(_DWORD *)(*a1 + 4) = a2;
  else
    a1[1] = a2;
  ++a1[2];
  *a1 = a2;
  return result;
}
