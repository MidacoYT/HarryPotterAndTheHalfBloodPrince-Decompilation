/* Verified exact body at 0x6ea266; semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6EA1F1(int a1, int a2, float *a3, _WORD *a4);
_DWORD *__cdecl fn_006EA266(_DWORD *a1)
{
  _DWORD *result; // eax

  result = a1;
  a1[1] = 0;
  *a1 = sub_6EA1F1;
  return result;
}
