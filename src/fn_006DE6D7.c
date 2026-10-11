#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD off_71B62C;
int __fastcall sub_6DE6D7(_DWORD *this, void *hp6_unused_edx)
{
  *this = &off_71B62C;
  return sub_6DE7D0();
}
