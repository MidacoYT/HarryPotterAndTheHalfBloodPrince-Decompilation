#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_6DE5B0(_DWORD *this, void *hp6_unused_edx)
{
  int v2; // eax
  int v3; // eax

  v2 = this[282];
  if ( v2 )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)v2 + 32))(v2);
    v3 = this[282];
    if ( v3 )
    {
      (*(void (__stdcall **)(_DWORD))(*(_DWORD *)v3 + 8))(this[282]);
      this[282] = 0;
    }
  }
  return 0;
}
