#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B7D8;
int __cdecl sub_6EACBE(int a1)
{
  int v1; // eax
  int (__cdecl *v2)(_DWORD); // ecx

  v1 = dword_89B7D8 + 92 * a1;
  v2 = *(int (__cdecl **)(_DWORD))(v1 + 68);
  if ( v2 )
    return v2(*(_DWORD *)(v1 + 72));
  else
    return -1;
}
