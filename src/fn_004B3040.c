/* Verified exact body at 0x4b3040 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int sub_4B3060(void);
int __fastcall fn_004B3040(_DWORD *this, void *hp6_unused_edx)
{
  int result; // eax

  sub_4B3060();
  result = 0;
  this[5] = 0;
  this[8] = 0;
  return result;
}
