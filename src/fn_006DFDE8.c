#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_89B438;
extern int __cdecl sub_6E03C5(int a1, int a2);
extern int __cdecl sub_6E0778(int a1);
int __cdecl sub_6DFDE8(int a1, int a2)
{
  int v3; // eax
  int v4; // edx
  int v5; // [esp-8h] [ebp-8h]

  if ( !byte_89B438 )
    return -10;
  v3 = sub_6E0778(a1);
  if ( !v3 )
    return -8;
  v4 = a2;
  if ( a2 > 0x4000 )
    v4 = 0x4000;
  v5 = *(_DWORD *)(v3 + 4);
  *(_WORD *)(v3 + 248) = v4;
  sub_6E03C5(v5, v4);
  return 0;
}
