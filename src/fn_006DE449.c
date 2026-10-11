#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD off_71B5E8;
extern int __cdecl sub_6DCBC7(int a1, int a2);
_DWORD *__fastcall sub_6DE449(_DWORD *this, void *hp6_unused_edx,  char a2)
{
  *this = &off_71B5E8;
  sub_6DE735();
  if ( (a2 & 1) != 0 )
    sub_6DCBC7((int)this, 1124);
  return this;
}
