/* Verified exact body at 0x631d10 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_D7A038;
char __fastcall fn_00631D10(_DWORD *this, void *hp6_unused_edx)
{
  *(_DWORD *)(dword_D7A038 + 45172) = this[1];
  return 1;
}
