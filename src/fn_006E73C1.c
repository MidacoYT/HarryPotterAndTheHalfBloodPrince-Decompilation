#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_89B43F;
extern _BYTE byte_89B5D6;
extern _DWORD dword_89B7D8;
extern int __cdecl sub_6E336B(signed int a1);
extern int __cdecl sub_6E7880(_DWORD *a1, int a2);
extern int __cdecl sub_6EA901(int a1, int a2);
extern int __cdecl sub_6EAAE3(int a1, char a2, int a3);
int __cdecl sub_6E73C1(int a1, int a2)
{
  int v2; // esi
  int v3; // edi
  int v4; // eax

  v2 = dword_89B7D8 + 92 * a1;
  v3 = 0;
  if ( a2 > 0x40000 )
    a2 = 0x40000;
  if ( !*(_DWORD *)(v2 + 80) )
  {
    v4 = sub_6E336B(60);
    *(_DWORD *)(v2 + 80) = v4;
    if ( (unsigned __int8)byte_89B5D6 >= 0x32u )
      v3 = 1;
    *(_DWORD *)(v4 + 4) = 0;
    *(_WORD *)(*(_DWORD *)(v2 + 80) + 24) = 160;
    *(_BYTE *)(*(_DWORD *)(v2 + 80) + 26) = 0;
    sub_6EAAE3(*(_DWORD *)(v2 + 80), byte_89B43F, v3);
    sub_6E7880(v2 + 64, *(_DWORD *)(v2 + 80));
  }
  return sub_6EA901(*(_DWORD *)(v2 + 80), a2);
}
