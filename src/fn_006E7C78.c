/* Verified exact body at 0x6e7c78 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E7BE2(int a1, int a2, int a3, float *a4);
extern int __cdecl sub_6E7C5B(int a1);
int __cdecl fn_006E7C78(int a1)
{
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 12) = 0;
  *(_DWORD *)(a1 + 16) = 0;
  *(_DWORD *)(a1 + 20) = 0;
  *(_BYTE *)(a1 + 27) = 0;
  *(_DWORD *)(a1 + 4) = sub_6E7C5B;
  *(_DWORD *)a1 = sub_6E7BE2;
  *(_DWORD *)(a1 + 32) = 0;
  *(_DWORD *)(a1 + 28) = 0;
  return 0;
}
