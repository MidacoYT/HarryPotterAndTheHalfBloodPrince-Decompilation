#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B2B8;
int __cdecl sub_6E70B6(int a1, int a2)
{
  int result; // eax
  int (__cdecl *v3)(_DWORD, int); // ecx

  result = dword_89B2B8 + 136 * a1;
  v3 = *(int (__cdecl **)(_DWORD, int))(result + 120);
  if ( v3 )
    return v3(*(_DWORD *)(result + 96), a2);
  return result;
}
