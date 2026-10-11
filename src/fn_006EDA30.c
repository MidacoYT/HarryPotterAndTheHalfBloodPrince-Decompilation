#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_6EDA30(_DWORD *this, void *hp6_unused_edx,  int a2)
{
  int result; // eax

  result = a2;
  this[12] = 0;
  this[13] = 0;
  this[9] = a2;
  this[10] = a2;
  this[11] = a2;
  return result;
}
