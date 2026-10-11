#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

bool __fastcall fn_00426B00(void *hp6_receiver, void *hp6_unused_edx)
{
  int v1; // eax
  bool result; // al

  result = 0;
  if ( hp6_receiver )
  {
    v1 = (*(int (__thiscall **)(void *))(*(_DWORD *)hp6_receiver + 16))(hp6_receiver);
    if ( v1 == 3 || v1 == 4 || v1 == 6 )
      return 1;
  }
  return result;
}

