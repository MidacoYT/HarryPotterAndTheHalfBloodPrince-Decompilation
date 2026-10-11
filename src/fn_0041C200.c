/* Verified exact body at 0x41c200 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __stdcall sub_41C050(int a1);
extern void __stdcall sub_41C0D0(int a1);
void __fastcall fn_0041C200(_DWORD *this, void *hp6_unused_edx,  int a2)
{
  this[3] = 0;
  sub_41C050((int)this);
  sub_41C0D0((int)this);
}
