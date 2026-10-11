/* Verified exact body at 0x5cda40 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall fn_005CDA40(_DWORD *this, void *hp6_unused_edx)
{
  int v1; // eax

  v1 = this[317];
  if ( v1 == 7 )
  {
    if ( (int)this[798] >= 2 || (int)this[799] >= 2 )
      return 1;
  }
  else if ( v1 == 8 || v1 == 9 || v1 == 10 || v1 == 11 || v1 == 12 || v1 == 13 )
  {
    return 1;
  }
  return 0;
}
