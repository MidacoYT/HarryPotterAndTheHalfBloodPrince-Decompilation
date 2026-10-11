#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E0F39(char *a1, int a2, int a3, struct _exception *a4, int a5, int a6, int a7);
int __cdecl sub_6E1531(int a1, char *a2, int a3, int a4, struct _exception *a5, int a6)
{
  return sub_6E0F39(a2, a3, a4, a5, a6, a1, 1);
}
