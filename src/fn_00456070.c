/* Verified exact body at 0x456070 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

_DWORD *__fastcall fn_00456070(int a1, _DWORD *a2)
{
  _DWORD *v2; // eax
  int v3; // ecx
  _DWORD *result; // eax
  int v5; // ecx

  v2 = a2 + 6;
  v3 = 175;
  do
  {
    *v2 = 0;
    v2 += 6;
    --v3;
  }
  while ( v3 );
  result = a2 + 1056;
  v5 = 100;
  do
  {
    *result = 0;
    result += 6;
    --v5;
  }
  while ( v5 );
  a2[1651] = 0;
  return result;
}
