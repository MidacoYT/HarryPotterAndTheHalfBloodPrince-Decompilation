#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern void __cdecl sub_6CA000(void *Block);
extern void __cdecl sub_6CA130(int a1);
void __cdecl sub_6CA300(int *a1)
{
  if ( *a1 )
  {
    sub_6CA130(*a1);
    sub_6CA000((void *)*a1);
    *a1 = 0;
  }
}
