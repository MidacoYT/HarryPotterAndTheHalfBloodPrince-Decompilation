/* Verified exact body at 0x631d50 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_D7A038;
char __fastcall fn_00631D50(float *this, void *hp6_unused_edx)
{
  *(float *)(dword_D7A038 + 244) = this[1];
  return 1;
}
