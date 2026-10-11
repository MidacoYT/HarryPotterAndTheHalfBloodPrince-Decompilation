/* Verified exact body at 0x65ff90 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __stdcall fn_0065FF90(int a1)
{
  int v1; // ecx
  int v2; // edx
  int result; // eax

  v1 = 1;
  v2 = 32;
  result = 0;
  do
  {
    if ( (*(_DWORD *)(a1 + 4) & v1) != 0 )
      ++result;
    v1 *= 2;
    --v2;
  }
  while ( v2 );
  return result;
}
