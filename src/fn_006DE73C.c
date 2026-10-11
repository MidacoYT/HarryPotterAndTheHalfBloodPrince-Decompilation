#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6DCAFE(int a1, int a2, int a3);
int __fastcall sub_6DE73C(_DWORD *this, void *hp6_unused_edx)
{
  this[2] = 0;
  this[1] = 0;
  sub_6DCAFE((int)(this + 1), 0, 536);
  return sub_6DCAFE((int)(this + 135), 0, 24);
}
