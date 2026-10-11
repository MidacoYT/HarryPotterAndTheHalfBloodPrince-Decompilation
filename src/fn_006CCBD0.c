#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl sub_6CCBD0(int a1)
{
  int result; // eax

  result = a1;
  *(_DWORD *)(a1 + 448) = 8;
  *(_DWORD *)(a1 + 452) = 8;
  return result;
}
