#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_4EEC80(_DWORD *this, void *hp6_unused_edx,  int a2)
{
  int v3; // eax
  int v4; // ecx
  int result; // eax

  v3 = sub_4EEDE0();
  v4 = this[15];
  if ( v4 )
  {
    *(_DWORD *)(v4 + 56) = this[14];
  }
  else if ( *(_DWORD **)(v3 + 8) == this )
  {
    *(_DWORD *)(v3 + 8) = this[14];
  }
  result = this[14];
  if ( result )
    *(_DWORD *)(result + 60) = this[15];
  this[14] = 0;
  this[15] = 0;
  return result;
}
