/* Verified exact body at 0x4ccc30 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_D2AB2C;
extern _DWORD dword_D2AB28;
extern _WORD word_D2AB2E;
char __cdecl fn_004CCC30(unsigned __int8 a1, char a2)
{
  char result; // al

  result = a2;
  *(_BYTE *)(a1
           + dword_D2AB28
           + (unsigned __int8)byte_D2AB2C
           * (((unsigned __int16)word_D2AB2E >> 3) + 2 * (unsigned __int16)word_D2AB2E + 1)) = a2;
  return result;
}
