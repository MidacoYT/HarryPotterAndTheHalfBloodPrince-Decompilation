/* Verified exact body at 0x633050 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E122C(_WORD *a1);
int fn_00633050()
{
  _WORD v1[6]; // [esp+0h] [ebp-Ch] BYREF

  sub_6E122C(v1);
  return v1[0];
}
