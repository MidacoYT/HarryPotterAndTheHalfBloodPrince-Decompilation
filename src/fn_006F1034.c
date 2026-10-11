#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B7D8;
extern int __cdecl sub_6E336B(signed int a1);
extern int __cdecl sub_6E7880(_DWORD *a1, int a2);
int __cdecl sub_6F1034(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // ebx

  v3 = dword_89B7D8 + 92 * a1;
  v4 = sub_6E336B(*(_DWORD *)(a3 + 4));
  (*(void (__cdecl **)(int, _DWORD, int))(a3 + 12))(v4, *(_DWORD *)a3, a2);
  *(_WORD *)(v4 + 24) = *(_WORD *)(a3 + 8);
  *(_DWORD *)v4 = *(_DWORD *)(a3 + 16);
  *(_DWORD *)(v4 + 4) = *(_DWORD *)(a3 + 20);
  *(_BYTE *)(v4 + 26) = 0;
  return sub_6E7880((_DWORD *)(v3 + 64), v4);
}
