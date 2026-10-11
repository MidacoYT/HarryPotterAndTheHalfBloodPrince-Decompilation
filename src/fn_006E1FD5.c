#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl sub_6E1FD5(int a1, int a2)
{
  if ( !a2 )
    *(_BYTE *)(a1 + 63) = 1;
  if ( a2 == 1 )
    *(_BYTE *)(a1 + 63) = 2;
  if ( a2 == 2 )
    *(_BYTE *)(a1 + 63) = 4;
  if ( a2 == 3 )
  {
    *(_BYTE *)(a1 + 63) = 5;
    *(_BYTE *)(a1 + 64) = 1;
  }
  if ( a2 == 8 )
    *(_BYTE *)(a1 + 63) = 2;
  return 0;
}
