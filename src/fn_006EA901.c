/* Verified exact body at 0x6ea901 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl fn_006EA901(int a1, int a2)
{
  int result; // eax

  result = a2;
  *(_DWORD *)(a1 + 28) = a2;
  return result;
}
