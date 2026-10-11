#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__fastcall sub_6B6A25(_DWORD *this, void *hp6_unused_edx)
{
  _DWORD *result; // eax
  int v2; // ecx

  result = this + 66;
  v2 = this[66];
  if ( v2 != 256 && v2 != 2 )
    *result = 0;
  return result;
}
