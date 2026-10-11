#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int sub_6E01A3();
extern int sub_6E01B0();
extern int __cdecl sub_6E3EAE(int a1, int *a2);
int __cdecl sub_6E6383(int a1)
{
  int v1; // esi

  sub_6E01A3();
  v1 = sub_6E3EAE(*(_DWORD *)(a1 + 4), *(int **)(a1 + 40));
  sub_6E01B0();
  return v1;
}
