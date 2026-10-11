/* Verified exact body at 0x6de7c7 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD off_71B670;
_DWORD *__fastcall fn_006DE7C7(_DWORD *this, void *hp6_unused_edx)
{
  _DWORD *result; // eax

  result = this;
  *this = &off_71B670;
  return result;
}
