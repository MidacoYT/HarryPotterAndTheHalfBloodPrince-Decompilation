#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E346D(int a1);
int __cdecl sub_6E7C5B(int a1)
{
  int result; // eax

  result = *(_DWORD *)(a1 + 32);
  if ( result )
  {
    result = sub_6E346D(*(_DWORD *)(a1 + 32));
    *(_DWORD *)(a1 + 32) = 0;
    *(_DWORD *)(a1 + 28) = 0;
  }
  return result;
}
