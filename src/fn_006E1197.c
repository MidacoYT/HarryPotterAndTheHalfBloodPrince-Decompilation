#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_852864;
int __cdecl sub_6E1197(int a1, int a2)
{
  int v2; // esi

  v2 = 4 * (dword_852864 + 10 * a1) + 532;
  return v2 + sub_6DF12F(a2);
}
