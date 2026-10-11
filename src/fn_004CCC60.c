/* Verified exact body at 0x4ccc60 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_D2AA64;
extern _DWORD dword_D2AA60;
extern _WORD word_D2AA66;
int __fastcall fn_004CCC60(int a1, char a2)
{
  int result; // eax
  int v3; // esi

  for ( result = 0; result < 4; ++result )
  {
    v3 = (unsigned __int8)result;
    *(_BYTE *)(v3
             + dword_D2AA60
             + (unsigned __int8)byte_D2AA64
             * (((unsigned __int16)word_D2AA66 >> 3) + 2 * (unsigned __int16)word_D2AA66 + 1)) = a2;
  }
  return result;
}
