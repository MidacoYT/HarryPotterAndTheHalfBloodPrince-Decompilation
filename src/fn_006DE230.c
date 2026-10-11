#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall fn_006DE230(_DWORD *hp6_receiver, void *hp6_unused_edx)
{
  int result; // eax
  int v3; // eax

  result = hp6_receiver[30];
  if ( result )
  {
    result = (*(int (__stdcall **)(int, int, _DWORD))(*(_DWORD *)result + 28))(result, 1, 0);
    if ( result == -2147024884 || result == -2147024866 || result == -2147220987 )
    {
      v3 = (*(int (__thiscall **)(_DWORD *))(*hp6_receiver + 16))(hp6_receiver);
      result = (*(int (__thiscall **)(int))(*(_DWORD *)v3 + 8))(v3);
      if ( result )
        return result;
      result = (*(int (__stdcall **)(_DWORD, int, _DWORD))(*(_DWORD *)hp6_receiver[30] + 28))(hp6_receiver[30], 1, 0);
    }
    if ( !result )
      hp6_receiver[28] = 1;
  }
  return result;
}

