/* Verified exact body at 0x58e560 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __stdcall sub_58E600(_DWORD *a1);
int __fastcall fn_0058E560(_DWORD *this, void *hp6_unused_edx)
{
  int result; // eax

  result = sub_58E600(this);
  this[131] &= 0xFFD7FFFF;
  return result;
}
