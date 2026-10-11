/* Verified exact body at 0x6ead91 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

float *__cdecl fn_006EAD91(float *a1)
{
  float *result; // eax

  result = a1;
  *a1 = 0.0;
  a1[1] = 0.0;
  a1[2] = 0.0;
  a1[3] = 0.0;
  a1[4] = 0.0;
  a1[5] = 0.0;
  a1[6] = 0.0;
  a1[7] = 0.0;
  return result;
}
