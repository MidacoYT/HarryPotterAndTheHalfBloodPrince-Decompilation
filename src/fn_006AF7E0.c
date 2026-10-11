/* Verified exact body at 0x6af7e0 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__cdecl fn_006AF7E0(_DWORD **a1, int a2, int a3, int a4, int a5)
{
  _DWORD *result; // eax

  result = *a1;
  if ( *a1 )
  {
    *result = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
    result[4] = 0;
  }
  else
  {
    result = 0;
  }
  *result = a2;
  result[1] = a3;
  result[3] = a4;
  result[2] = a5;
  return result;
}
