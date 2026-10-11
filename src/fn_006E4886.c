#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B2E4;
extern _DWORD dword_89B4A8;
unsigned int __cdecl sub_6E4886(int a1)
{
  int v1; // eax

  if ( a1 >= 0 && a1 < (unsigned __int16)dword_89B2E4 && (v1 = dword_89B4A8 + 8 * a1, *(_DWORD *)v1) )
    return *(_BYTE *)(v1 + 4) != 0 ? 0xFFFFFFEE : 0;
  else
    return -8;
}
