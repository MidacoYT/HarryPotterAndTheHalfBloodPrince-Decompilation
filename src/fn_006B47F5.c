#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6B492B(int a1, int a2);
void *__fastcall sub_6B47F5(void *this, void *hp6_unused_edx,  char a2)
{
  sub_6B562E();
  if ( (a2 & 1) != 0 )
    sub_6B492B(this, 1256);
  return this;
}
