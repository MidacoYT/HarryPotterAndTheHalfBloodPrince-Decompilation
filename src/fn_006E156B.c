#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_89B438;
extern int sub_6E01A3();
extern int sub_6E01B0();
extern _DWORD *__cdecl sub_6E3F71(int a1);
int __cdecl sub_6E156B(int a1, __int16 a2)
{
  int v2; // esi
  int v4; // eax

  v2 = -8;
  if ( !byte_89B438 )
    return -10;
  sub_6E01A3();
  v4 = sub_6E3F71(a1);
  if ( v4 )
  {
    *(_DWORD *)(v4 + 32) = a2;
    v2 = 0;
  }
  sub_6E01B0();
  return v2;
}
