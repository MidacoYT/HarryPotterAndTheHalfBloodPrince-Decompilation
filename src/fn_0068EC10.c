/* Verified exact body at 0x68ec10 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern float flt_8510B4;
double __cdecl fn_0068EC10(float a1)
{
  float v2; // [esp+0h] [ebp-4h]

  v2 = flt_8510B4;
  flt_8510B4 = a1;
  return v2;
}
