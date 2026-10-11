/* Verified exact body at 0x539940 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_FCADE8;
extern int __stdcall sub_53CB80(int a1, const char *a2);
int __fastcall fn_00539940(_DWORD *this, void *hp6_unused_edx)
{
  int result; // eax

  result = this[8];
  if ( result )
  {
    result = sub_53CB80(dword_FCADE8, *(const char **)(result + 108));
    this[11] = result;
  }
  return result;
}
