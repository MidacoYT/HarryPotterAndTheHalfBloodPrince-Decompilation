#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern void __cdecl sub_5DC710(int a1);
void *__fastcall sub_6DB392(void *this, void *hp6_unused_edx,  char a2)
{
  sub_6DB3B1();
  if ( (a2 & 1) != 0 )
    sub_5DC710((int)this);
  return this;
}
