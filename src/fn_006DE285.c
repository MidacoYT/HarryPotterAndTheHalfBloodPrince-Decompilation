#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall sub_6DE285(_DWORD *this, void *hp6_unused_edx)
{
  int result; // eax
  _BYTE v3[4]; // [esp+4h] [ebp-4h] BYREF

  result = this[30];
  if ( result )
  {
    result = (*(int (__stdcall **)(int, _BYTE *))(*(_DWORD *)result + 36))(result, v3);
    if ( (v3[0] & 1) != 0 )
    {
      result = (*(int (__stdcall **)(_DWORD))(*(_DWORD *)this[30] + 32))(this[30]);
      if ( !result )
        this[28] = 0;
    }
  }
  return result;
}
