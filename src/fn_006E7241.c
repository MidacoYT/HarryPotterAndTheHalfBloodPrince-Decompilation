#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B2B8;
int __cdecl sub_6E7241(int a1, int a2)
{
  int v2; // eax
  void (__cdecl *v3)(_DWORD, int); // ecx

  v2 = dword_89B2B8 + 136 * a1;
  v3 = *(void (__cdecl **)(_DWORD, int))(v2 + 112);
  if ( v3 )
    v3(*(_DWORD *)(v2 + 92), a2);
  return 0;
}
