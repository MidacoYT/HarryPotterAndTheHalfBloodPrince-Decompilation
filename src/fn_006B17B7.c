#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6B22C3(int a1);
extern __int64 __cdecl sub_6B2359(int a1);
extern int __cdecl sub_6B24F2(int a1, int a2, int a3, int a4, int a5, int a6);
int __cdecl sub_6B17B7(int a1, int a2, int a3, int a4, int a5)
{
  int v5; // esi

  v5 = sub_6B24F2(a1, a2, a3, a4, a5, 0);
  sub_6B22C3(v5);
  return sub_6B2359(v5);
}
