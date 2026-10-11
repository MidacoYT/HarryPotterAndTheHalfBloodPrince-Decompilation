/* Verified exact body at 0x631c00 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_D7A038;
char __fastcall fn_00631C00(_DWORD **this, void *hp6_unused_edx)
{
  *this[1] = dword_D7A038 + 336;
  return 1;
}
