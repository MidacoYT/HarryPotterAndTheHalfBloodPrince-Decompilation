#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD off_71B62C;
extern int __cdecl sub_6DCBC7(int a1, int a2);
_DWORD *__fastcall sub_6DE70D(_DWORD *this, void *hp6_unused_edx,  char a2)
{
  *this = &off_71B62C;
  sub_6DE7D0();
  if ( (a2 & 1) != 0 )
    sub_6DCBC7((int)this, 120);
  return this;
}
