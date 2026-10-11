#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B2B8;
extern int sub_6E01A3();
extern int sub_6E01B0();
extern int __cdecl sub_6E297F(int a1);
extern int __cdecl sub_6E346D(int a1);
int __cdecl sub_6E2B09(int a1)
{
  sub_6E297F(a1);
  sub_6E01A3();
  sub_6E346D(dword_89B2B8);
  sub_6E01B0();
  return 0;
}
