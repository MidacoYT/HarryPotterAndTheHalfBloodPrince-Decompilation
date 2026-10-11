#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E77CB(int a1, int a2, int a3, void *a4);
_DWORD *__cdecl sub_6E77F7(_DWORD *a1, int a2)
{
  _DWORD *result; // eax

  result = a1;
  a1[1] = 0;
  *a1 = sub_6E77CB;
  a1[7] = a2;
  return result;
}
