#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89AE38;
extern _DWORD dword_89B388;
extern void nullsub_9();
extern int __cdecl sub_6D9653(int a1, int a2, int a3, int a4);
extern int __cdecl sub_6D97A0(int a1);
extern int sub_6DEC9B();
extern void __cdecl sub_6E3FA7();
int sub_6DECA0()
{
  dword_89B388 = (int)nullsub_9;
  if ( !dword_89AE38 )
  {
    sub_6D9653((int)sub_6DEC9B, 0, 1, 0);
    dword_89AE38 = 1;
  }
  sub_6D97A0((int)sub_6E3FA7);
  return 0;
}
