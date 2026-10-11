#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_6D7391(_DWORD *this, void *hp6_unused_edx,  _DWORD *a2,  _DWORD *a3,  _DWORD *a4,  _DWORD *a5)
{
  int result; // eax

  *a2 = this[4];
  *a3 = this[5];
  *a4 = this[6];
  result = this[7];
  *a5 = result;
  return result;
}
