#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl sub_6DFFA8(int a1)
{
  *(_WORD *)(a1 + 20) = -1;
  *(_BYTE *)(a1 + 2) = 60;
  *(_WORD *)(a1 + 12) = 4096;
  *(_WORD *)(a1 + 14) = 4096;
  *(_WORD *)(a1 + 16) = 4096;
  *(_WORD *)(a1 + 22) = 0;
  *(_BYTE *)(a1 + 3) = 127;
  *(_BYTE *)a1 = 127;
  *(_BYTE *)(a1 + 4) = 127;
  *(_BYTE *)(a1 + 1) = 64;
  *(_BYTE *)(a1 + 5) = 0;
  *(_WORD *)(a1 + 8) = 0;
  *(_WORD *)(a1 + 10) = 0;
  return 0;
}
