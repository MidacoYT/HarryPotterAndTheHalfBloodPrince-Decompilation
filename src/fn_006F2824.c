/* Verified exact body at 0x6f2824 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

float *__fastcall fn_006F2824(float *this, void *hp6_unused_edx,  float *a2)
{
  float *result; // eax

  result = a2;
  this[38] = *a2;
  this[39] = a2[1];
  return result;
}
