#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B7D8;
int __cdecl sub_6E5936(int a1, int a2, float a3)
{
  int result; // eax

  result = 92 * a1;
  *(float *)(*(_DWORD *)(92 * a1 + dword_89B7D8 + 56) + 4 * a2) = a3;
  *(_BYTE *)(92 * a1 + dword_89B7D8 + 1) = 1;
  return result;
}
