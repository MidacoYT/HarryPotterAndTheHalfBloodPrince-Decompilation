#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_6B2CBD(int *this, void *hp6_unused_edx)
{
  int result; // eax
  int v2; // edx
  int v3; // edx

  result = *this;
  if ( *this )
  {
    if ( result == this[1] )
    {
      this[1] = 0;
      *this = 0;
    }
    else
    {
      v2 = *(_DWORD *)(result + 8);
      if ( v2 )
        v3 = v2 - 8;
      else
        v3 = 0;
      *this = v3;
    }
    --this[2];
    *(_DWORD *)(result + 8) = 0;
  }
  return result;
}
