/* Verified exact body at 0x68a200 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _WORD word_B1089C;
char *__fastcall fn_0068A200(char *this, void *hp6_unused_edx)
{
  char *result; // eax
  _WORD *v2; // esi
  _DWORD *v3; // edx
  int v4; // edi

  result = this;
  v2 = this + 480;
  v3 = this + 320;
  v4 = 40;
  do
  {
    *(v3 - 40) = 0;
    *(v3 - 80) = 0;
    *v3 = -1;
    *v2++ = word_B1089C;
    ++v3;
    --v4;
  }
  while ( v4 );
  return result;
}
