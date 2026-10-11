#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __fastcall fn_00637460(_DWORD *hp6_receiver, void *hp6_unused_edx)
{
  int result; // eax

  result = (*(int (__thiscall **)(_DWORD *))(*hp6_receiver + 52))(hp6_receiver);
  hp6_receiver[7] |= 8u;
  return result;
}

