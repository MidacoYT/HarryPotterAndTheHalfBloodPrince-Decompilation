#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl sub_6E78C0(int *a1, int a2)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx

  result = *a1;
  if ( a2 == *a1 )
  {
    result = *(_DWORD *)(result + 8);
    *a1 = result;
  }
  else
  {
    while ( *(_DWORD *)(result + 8) && *(_DWORD *)(result + 8) != a2 )
      result = *(_DWORD *)(result + 8);
    v3 = *(_DWORD *)(result + 8);
    if ( v3 && v3 == a2 )
    {
      v4 = *(_DWORD *)(v3 + 8);
      if ( v4 )
        *(_DWORD *)(v4 + 16) = result;
      *(_DWORD *)(result + 8) = *(_DWORD *)(*(_DWORD *)(result + 8) + 8);
    }
  }
  return result;
}
