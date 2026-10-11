#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E6383(int a1);
int __fastcall sub_6DF9EC(_DWORD *this, void *hp6_unused_edx)
{
  if ( *this == 1180189267 || *this == 1129529939 )
  {
    if ( !this[9] )
      this[10] = sub_6E6383(this);
    this[9] = 1;
  }
  return 0;
}
