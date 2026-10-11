/* Verified exact body at 0x68bdd0 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_8929CC;
extern _DWORD dword_8929D0;
extern _DWORD off_714C90;
extern int __cdecl sub_68BC00(int a1);
int __cdecl fn_0068BDD0(int a1)
{
  _DWORD *v1; // eax

  dword_8929CC = a1;
  v1 = (_DWORD *)sub_68BC00(4);
  if ( v1 )
  {
    *v1 = &off_714C90;
    dword_8929D0 = (int)v1;
  }
  else
  {
    dword_8929D0 = 0;
  }
  return 0;
}
