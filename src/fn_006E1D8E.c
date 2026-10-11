/* Verified exact body at 0x6e1d8e; semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E1CA3(_BYTE *a1);
int fn_006E1D8E()
{
  int result; // eax

  result = sub_6E1CA3(0);
  if ( result >= 0 )
    return 0;
  return result;
}
