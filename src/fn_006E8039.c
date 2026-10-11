#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E7FF0(int a1, int a2, int a3, int a4);
extern float *__cdecl sub_6EAD91(float *a1);
int __cdecl sub_6E8039(int a1)
{
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 12) = 0;
  *(_DWORD *)(a1 + 16) = 0;
  *(_DWORD *)(a1 + 20) = 0;
  *(_BYTE *)(a1 + 27) = 0;
  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)a1 = sub_6E7FF0;
  sub_6EAD91(a1 + 28);
  return 0;
}
