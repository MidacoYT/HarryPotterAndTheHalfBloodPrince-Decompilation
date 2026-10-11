#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_66A780(int a1);
extern int sub_66C1D0(void);
char __stdcall sub_5FCE80(_DWORD *a1, int a2, int a3)
{
  if ( a1 && *a1 == 0x10000 )
  {
    sub_66C1D0();
    sub_66C240();
    sub_66A780(a1);
  }
  return 1;
}
