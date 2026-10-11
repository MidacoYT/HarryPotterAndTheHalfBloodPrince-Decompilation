#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_6B45AE(_DWORD *this, void *hp6_unused_edx)
{
  int result; // eax

  *this = -1;
  this[1] = -1;
  result = 0;
  this[2] = 0;
  this[3] = 0;
  this[4] = 0;
  *((_BYTE *)this + 20) = 0;
  *((_BYTE *)this + 21) = 0;
  return result;
}
