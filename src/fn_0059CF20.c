/* Verified exact body at 0x59cf20 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__fastcall fn_0059CF20(int a1, int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // ecx

  result = *(_DWORD **)(a1 + 41780);
  v3 = &result[6 * *(_DWORD *)(a1 + 41776)];
  if ( !a2 || result == v3 )
    return 0;
  while ( !result || *result != a2 )
  {
    result += 6;
    if ( result == v3 )
      return 0;
  }
  return result;
}
