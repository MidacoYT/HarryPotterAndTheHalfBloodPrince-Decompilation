/* Verified exact body at 0x5487e0 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_87C2C0;
extern _DWORD dword_89D7B0;
int fn_005487E0()
{
  int result; // eax

  result = dword_87C2C0;
  if ( !dword_87C2C0 || dword_89D7B0 != *(_DWORD *)(dword_87C2C0 + 80) )
    return 0;
  return result;
}
