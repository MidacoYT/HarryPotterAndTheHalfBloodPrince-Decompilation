/* Verified exact body at 0x6a5600 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall fn_006A5600(_DWORD *this, void *hp6_unused_edx,  int a2)
{
  int result; // eax
  int v3; // edx

  result = a2;
  v3 = this[11];
  *(_DWORD *)(*(_DWORD *)(a2 + 8) + 12) = *(_DWORD *)(a2 + 12);
  *(_DWORD *)(*(_DWORD *)(a2 + 12) + 8) = *(_DWORD *)(a2 + 8);
  *(_DWORD *)(a2 + 8) = v3;
  *(_DWORD *)(a2 + 12) = *(_DWORD *)(v3 + 12);
  *(_DWORD *)(*(_DWORD *)(v3 + 12) + 8) = a2;
  *(_DWORD *)(v3 + 12) = a2;
  --this[20];
  ++this[19];
  return result;
}
