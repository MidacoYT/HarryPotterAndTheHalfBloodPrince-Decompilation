/* Verified exact body at 0x6edac0; semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD off_724780;
_DWORD *__fastcall fn_006EDAC0(_DWORD *this, void *hp6_unused_edx)
{
  _DWORD *result; // eax

  result = this;
  this[19] = 0;
  *this = &off_724780;
  *((_BYTE *)this + 71) = 0;
  return result;
}
