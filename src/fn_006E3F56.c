/* Verified exact body at 0x6e3f56 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl fn_006E3F56(int a1, float a2, int a3)
{
  int result; // eax

  result = a3;
  *(float *)(a3 + 4 * a1 + 104) = a2;
  *(_DWORD *)(a3 + 128) = 1;
  return result;
}
