#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_6B63BB(_DWORD *this, void *hp6_unused_edx,  int a2,  int a3)
{
  int result; // eax

  if ( a2 == 1 )
  {
    this[31] |= a3;
    result = ~a3;
  }
  else
  {
    if ( a2 == 2 )
    {
      this[32] |= a3;
      result = ~a3;
      this[31] &= ~a3;
      return result;
    }
    result = ~a3;
    this[31] &= ~a3;
  }
  this[32] &= result;
  return result;
}
