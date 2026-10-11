/* Verified exact body at 0x6ca330; semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl fn_006CA330(int a1, int a2)
{
  int result; // eax

  result = a2;
  *(_DWORD *)(a1 + 108) = a2;
  return result;
}
