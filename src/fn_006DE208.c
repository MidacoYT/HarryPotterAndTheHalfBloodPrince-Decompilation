#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_6DE208(_DWORD *this, void *hp6_unused_edx)
{
  int v2; // eax
  _BYTE v4[4]; // [esp+4h] [ebp-4h] BYREF

  v2 = this[30];
  if ( v2 )
  {
    (*(void (__stdcall **)(int, _BYTE *))(*(_DWORD *)v2 + 36))(v2, v4);
    this[28] = v4[0] & 1;
  }
  return this[28];
}
