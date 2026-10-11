/* Verified exact body at 0x5ddc40 with VC8 SP1; source semantics remain inferred. */
#include "scalar_aliases.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

unsigned int __fastcall fn_005DDC40(_DWORD *this, void *hp6_unused_edx)
{
  unsigned int result; // eax

  result = ((this[1] & 0x7FFFFFF8) - 9) & 0xFFFFFFF8;
  this[1] = result | this[1] & 0x80000007;
  *(_DWORD *)((char *)this + result) = result;
  *(_DWORD *)((char *)this + result + 4) = 8;
  *(_DWORD *)((char *)this + result + 8) = 8;
  *(_DWORD *)((char *)this + result + 12) = 9;
  return result;
}
