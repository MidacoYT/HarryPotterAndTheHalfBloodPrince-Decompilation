/* Verified exact body at 0x40d830 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int sub_40D880(void);
int __fastcall fn_0040D830(_DWORD *this, void *hp6_unused_edx)
{
  int v2; // eax
  int v3; // ecx
  int result; // eax

  v2 = sub_40D880();
  v3 = this[90];
  if ( v3 )
    *(_DWORD *)(v3 + 356) = this[89];
  else
    *(_DWORD *)(v2 + 12) = this[89];
  result = this[89];
  if ( result )
    *(_DWORD *)(result + 360) = this[90];
  return result;
}
