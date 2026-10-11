#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_89B438;
extern int __cdecl sub_6E0778(int a1);
extern int __cdecl sub_6E17CB(int a1, int a2);
int __cdecl sub_6E1948(int a1, int a2)
{
  int v3; // esi
  int v4; // eax
  int v5; // eax
  int v6; // [esp-Ch] [ebp-Ch]

  if ( !byte_89B438 )
    return -10;
  v3 = a2;
  v4 = 0x2000;
  if ( a2 > 0x2000 || (v4 = 2048, a2 < 2048) )
    v3 = v4;
  v5 = sub_6E0778(a1);
  if ( !v5 )
    return -8;
  v6 = *(_DWORD *)(v5 + 4);
  *(_WORD *)(v5 + 250) = v3;
  sub_6E17CB(v6, v3);
  return 0;
}
