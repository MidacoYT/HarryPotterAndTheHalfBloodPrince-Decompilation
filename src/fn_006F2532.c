/* Verified exact body at 0x6f2532 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall fn_006F2532(_DWORD *this, void *hp6_unused_edx,  _DWORD *a2,  int a3)
{
  int result; // eax

  this[1] = *a2;
  this[855] = a2[2];
  result = a2[1];
  this[849] = result;
  return result;
}
