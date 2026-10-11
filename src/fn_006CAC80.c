#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern void __cdecl sub_6CA000(void *Block);
void __cdecl sub_6CAC80(void **a1)
{
  void **v1; // esi
  void *v2; // eax

  v1 = (void **)*a1;
  if ( *a1 )
  {
    if ( v1[98] )
      sub_6CA000(v1[98]);
    v2 = v1[99];
    v1[98] = 0;
    v1[96] = 0;
    if ( v2 )
      sub_6CA000(v2);
    v1[99] = 0;
    v1[97] = 0;
    sub_6CA000(*a1);
    *a1 = 0;
  }
}
