#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

int __cdecl sub_6E0350(int a1)
{
  _DWORD *v1; // ecx
  int v2; // esi
  _DWORD *v3; // ecx
  _WORD *v4; // eax
  int v5; // esi

  *(_BYTE *)(a1 + 2) = 0;
  *(_WORD *)a1 = 0;
  *(_BYTE *)(a1 + 3) = 127;
  *(_BYTE *)(a1 + 4) = 64;
  *(_BYTE *)(a1 + 5) = 0;
  *(_BYTE *)(a1 + 6) = 0;
  *(_BYTE *)(a1 + 7) = 0;
  *(_WORD *)(a1 + 8) = 0;
  v1 = (_DWORD *)(a1 + 88);
  v2 = 4;
  do
  {
    *(v1 - 4) = 0;
    *v1++ = 0;
    --v2;
  }
  while ( v2 );
  v3 = (_DWORD *)(a1 + 24);
  v4 = (_WORD *)(a1 + 12);
  v5 = 6;
  do
  {
    *v4 = 0;
    *v3 = 0;
    ++v4;
    ++v3;
    --v5;
  }
  while ( v5 );
  return 0;
}
