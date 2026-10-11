/* Verified exact body at 0x6e7d68 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E7D1C(int a1, int a2, int a3, float *a4);
int __cdecl fn_006E7D68(int a1)
{
  *(float *)(a1 + 28) = 0.0;
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 12) = 0;
  *(_DWORD *)(a1 + 16) = 0;
  *(_DWORD *)(a1 + 20) = 0;
  *(_BYTE *)(a1 + 27) = 0;
  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)a1 = sub_6E7D1C;
  return 0;
}
