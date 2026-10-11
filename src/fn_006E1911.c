#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_89B438;
extern int __cdecl sub_6E0778(int a1);
extern int __cdecl sub_6E172B(int a1, char a2);
int __cdecl sub_6E1911(int a1, char a2)
{
  int v3; // eax
  int v4; // [esp-8h] [ebp-8h]

  if ( !byte_89B438 )
    return -10;
  v3 = sub_6E0778(a1);
  if ( !v3 )
    return -8;
  v4 = *(_DWORD *)(v3 + 4);
  *(_BYTE *)(v3 + 240) = a2;
  sub_6E172B(v4, a2);
  return 0;
}
