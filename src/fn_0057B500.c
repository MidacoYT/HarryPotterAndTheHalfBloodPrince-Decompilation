/* Verified exact body at 0x57b500 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__fastcall fn_0057B500(int a1, int a2)
{
  _DWORD *v2; // eax
  unsigned int v3; // esi
  int v4; // ecx
  _DWORD *result; // eax

  v2 = *(_DWORD **)a2;
  v3 = 32 * *(_DWORD *)(a2 + 12) + *(_DWORD *)a2 - 16;
  if ( *(_DWORD *)a2 < v3 )
  {
    do
    {
      *v2 = v2 + 4;
      v2[1] = 0;
      v2[2] = 0;
      v2 += 4;
    }
    while ( (unsigned int)v2 < v3 );
  }
  *v2 = 0;
  v2[1] = 0;
  v2[2] = 0;
  v4 = *(_DWORD *)(a2 + 12);
  result = *(_DWORD **)a2;
  *(_DWORD *)(a2 + 4) = *(_DWORD *)a2;
  *(_DWORD *)(a2 + 24) = 2 * v4;
  return result;
}
