#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6F16F9(int a1, int a2);
int __cdecl sub_6EACDD(int a1, int a2)
{
  return 16 * sub_6F16F9(a1, a2 / 16);
}
