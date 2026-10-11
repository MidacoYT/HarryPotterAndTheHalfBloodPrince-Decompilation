#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD off_71B5C0;
_DWORD *__fastcall sub_6DDE6E(_DWORD *this, void *hp6_unused_edx)
{
  sub_6DE687();
  this[30] = 0;
  *this = &off_71B5C0;
  return this;
}
