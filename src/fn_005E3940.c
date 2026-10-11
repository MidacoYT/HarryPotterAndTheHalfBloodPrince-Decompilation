/* Verified exact body at 0x5e3940 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall fn_005E3940(_DWORD *a1, _DWORD *a2, int a3)
{
  int result; // eax

  result = a3;
  *(_BYTE *)(a3 + 5) = 1;
  *(_DWORD *)(a3 + 8) = *a1;
  *(_DWORD *)(a3 + 12) = a1[1];
  *(_DWORD *)(a3 + 16) = a1[2];
  *(_DWORD *)(a3 + 20) = *a2;
  if ( *a2 == 8 )
    *(_BYTE *)(a3 + 4) = 1;
  return result;
}
