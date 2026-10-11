#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6C9590(_DWORD *a1);
extern void __cdecl sub_6CA300(int *a1);
extern void __cdecl sub_6CAC80(void **a1);
extern void __cdecl sub_6CC580(int a1);
extern void __cdecl sub_6CC810(int a1);
int __cdecl sub_6C9E30(_DWORD *a1)
{
  if ( *a1 )
  {
    sub_6CAC80(*a1 + 316);
    sub_6CA300(*a1 + 668);
    sub_6CC580(*a1);
    sub_6CC810(*a1);
    sub_6C9590(a1);
  }
  return 1;
}
