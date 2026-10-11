#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_89B438;
extern int __cdecl sub_6E0778(int a1);
extern void sub_6F4EB9();
int __cdecl sub_6E71E1(int a1, int a2)
{
  _DWORD *v3; // eax

  if ( !byte_89B438 )
    return -10;
  v3 = (_DWORD *)sub_6E0778(a1);
  if ( !v3 )
    return -8;
  sub_6F4EB9(*v3, a2);
  return 0;
}
