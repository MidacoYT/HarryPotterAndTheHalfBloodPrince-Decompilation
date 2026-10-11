#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_CF6348;
bool fn_00458470()
{
  int v0; // eax
  bool result; // al

  result = 0;
  if ( dword_CF6348 )
  {
    v0 = (*(int (__thiscall **)(int))(*(_DWORD *)dword_CF6348 + 16))(dword_CF6348);
    if ( v0 == 3 || v0 == 4 || v0 == 6 )
      return 1;
  }
  return result;
}

