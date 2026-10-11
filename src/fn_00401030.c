/* Verified exact body at 0x401030 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__fastcall fn_00401030(_DWORD *this, void *hp6_unused_edx,  int a2,  int a3)
{
  _DWORD *result; // eax

  result = this;
  *this = a2;
  this[1] = a3;
  this[2] = 0;
  return result;
}
