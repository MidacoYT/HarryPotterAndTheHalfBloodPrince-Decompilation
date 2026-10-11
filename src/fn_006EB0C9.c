#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD off_72446C;
_DWORD *__fastcall sub_6EB0C9(_DWORD *this, void *hp6_unused_edx)
{
  sub_6EDAC0();
  this[108] = 0;
  *this = &off_72446C;
  return this;
}
