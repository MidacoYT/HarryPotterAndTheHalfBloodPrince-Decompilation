/* Verified exact body at 0x6b6b05; semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__fastcall fn_006B6B05(_DWORD *this, void *hp6_unused_edx)
{
  _DWORD *result; // eax
  int v2; // ecx

  result = this + 2;
  v2 = 3;
  do
  {
    *result = 0;
    result += 21;
    --v2;
  }
  while ( v2 );
  return result;
}
