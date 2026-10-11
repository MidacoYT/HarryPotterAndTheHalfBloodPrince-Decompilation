/* Verified exact body at 0x6e590c with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B7D8;
int __cdecl fn_006E590C(int a1, int a2, float a3)
{
  int result; // eax

  result = 92 * a1;
  *(float *)(dword_89B7D8 + 4 * (a2 + 23 * a1) + 28) = a3;
  *(_BYTE *)(92 * a1 + dword_89B7D8 + 1) = 1;
  return result;
}
