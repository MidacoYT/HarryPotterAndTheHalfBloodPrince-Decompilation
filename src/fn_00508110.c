/* Verified exact body at 0x508110 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_D399C0;
extern int __stdcall sub_507740(_DWORD *a1);
extern int __stdcall sub_5080B0(int a1);
int __stdcall fn_00508110(char a1)
{
  if ( a1 )
    sub_5080B0(0);
  return sub_507740(&dword_D399C0);
}
