#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__fastcall sub_6DB335(_DWORD *this, void *hp6_unused_edx)
{
  _DWORD *result; // eax

  result = (_DWORD *)*this;
  if ( *this )
  {
    if ( result == (_DWORD *)this[1] )
    {
      this[1] = 0;
      *this = 0;
    }
    else
    {
      *this = *result;
    }
    --this[2];
    *result = 0;
  }
  return result;
}
