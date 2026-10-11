#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B2E4;
extern int sub_6E01A3();
extern int sub_6E01B0();
extern _DWORD *__cdecl sub_6E3D49(int a1, int a2, unsigned __int8 *Src);
_DWORD *__cdecl fn_006E6357(int a1, unsigned __int8 *Src)
{
  _DWORD *v2; // esi

  sub_6E01A3();
  v2 = sub_6E3D49(HIWORD(dword_89B2E4), *(_DWORD *)(a1 + 4), Src);
  sub_6E01B0();
  return v2;
}

