#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD off_71B94C;
_DWORD *__fastcall sub_6E8737(_DWORD *this, void *hp6_unused_edx)
{
  sub_6EB0C9();
  this[110] = 0;
  *this = &off_71B94C;
  return this;
}
