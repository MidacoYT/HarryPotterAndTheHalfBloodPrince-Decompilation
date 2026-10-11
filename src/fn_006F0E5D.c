#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E5FB2(int a1);
extern int __cdecl sub_6E5FD5(int a1);
extern int __cdecl sub_6E99FF(int a1);
extern int __cdecl sub_6F0D9A(int a1, int a2, int a3, double *a4);
int __cdecl sub_6F0E5D(int a1, int a2)
{
  int v2; // eax
  char v3; // al
  int result; // eax

  *(_DWORD *)a1 = sub_6F0D9A;
  v2 = sub_6E5FB2(*(_DWORD *)(a2 + 28));
  *(_DWORD *)(a1 + 40) = sub_6E99FF(v2);
  v3 = sub_6E5FD5(*(_DWORD *)(a2 + 28));
  *(_DWORD *)(a1 + 32) = -1;
  *(_BYTE *)(a1 + 49) = v3;
  result = 0;
  *(_DWORD *)(a1 + 28) = 0;
  *(_DWORD *)(a1 + 36) = 0;
  *(_BYTE *)(a1 + 48) = *(_BYTE *)(a2 + 24);
  *(_DWORD *)(a1 + 44) = 0;
  return result;
}
