/* Verified exact body at 0x641c20 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_CF1938;
int fn_00641C20()
{
  int result; // eax

  for ( result = dword_CF1938; result; result = *(_DWORD *)(result + 48) )
    *(_BYTE *)(result + 4) = 0;
  return result;
}
