#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

char __fastcall fn_00564C80(_DWORD *hp6_receiver, void *hp6_unused_edx)
{
  _BYTE *v1; // eax

  v1 = (_BYTE *)hp6_receiver[176];
  if ( v1 )
    LOBYTE(v1) = *v1;
  else
    return (hp6_receiver[187] >> 3) & 1;
  return (char)v1;
}

