#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_FD22B0;
extern int __cdecl sub_6CA3A0(int a1);
extern _DWORD *__cdecl sub_6CECC0(_DWORD *a1, _DWORD *a2, _DWORD *a3);
extern int __cdecl sub_6CF070(int a1);
extern int __cdecl sub_6CF100(int a1);
int sub_6CC4D0()
{
  int result; // eax
  _BYTE v1[4]; // [esp+0h] [ebp-Ch] BYREF
  int v2; // [esp+4h] [ebp-8h] BYREF
  int v3; // [esp+8h] [ebp-4h] BYREF

  sub_6CECC0(&v2, v1, &v3);
  result = v3;
  if ( v3 )
  {
    dword_FD22B0 = sub_6CF100;
  }
  else
  {
    result = v2;
    dword_FD22B0 = sub_6CF070;
    if ( !v2 )
      dword_FD22B0 = sub_6CA3A0;
  }
  return result;
}
