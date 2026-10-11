/* Verified exact body at 0x6b9718 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern void __cdecl __security_init_cookie();
extern int __tmainCRTStartup();
int fn_006B9718()
{
  __security_init_cookie();
  return __tmainCRTStartup();
}
