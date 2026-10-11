#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall fn_00654ED0(_DWORD *hp6_receiver, void *hp6_unused_edx,  int a2)
{
  if ( a2 < 0 || a2 >= (*(int (__thiscall **)(_DWORD *))(*hp6_receiver + 60))(hp6_receiver) )
    return 0;
  else
    return *(_DWORD *)(148 * a2 + hp6_receiver[4] + 136);
}

