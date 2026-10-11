#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall fn_00500E20(_DWORD *hp6_receiver, void *hp6_unused_edx,  int a2)
{
  if ( a2 == (*(int (__thiscall **)(_DWORD))(*(_DWORD *)hp6_receiver[4] + 40))(hp6_receiver[4]) )
    return hp6_receiver[4];
  else
    return 0;
}


