#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_FCAE00;
int fn_00581400()
{
  int result; // eax

  result = dword_FCAE00;
  if ( *(_DWORD *)(dword_FCAE00 + 12) )
    return (*(int (__thiscall **)(int))(*(_DWORD *)(*(_DWORD *)(dword_FCAE00 + 12) + 144) + 8))(*(_DWORD *)(dword_FCAE00 + 12) + 144);
  return result;
}

