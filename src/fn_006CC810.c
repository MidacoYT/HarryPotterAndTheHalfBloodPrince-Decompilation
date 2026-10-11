#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern void __cdecl sub_6CA000(void *Block);
void __cdecl sub_6CC810(int a1)
{
  if ( *(_DWORD *)(a1 + 584) )
    sub_6CA000(*(void **)(a1 + 584));
  if ( *(_DWORD *)(a1 + 592) )
    sub_6CA000(*(void **)(a1 + 592));
  if ( *(_DWORD *)(a1 + 600) )
    sub_6CA000(*(void **)(a1 + 600));
  if ( *(_DWORD *)(a1 + 608) )
    sub_6CA000(*(void **)(a1 + 608));
  *(_DWORD *)(a1 + 584) = 0;
  *(_DWORD *)(a1 + 592) = 0;
  *(_DWORD *)(a1 + 600) = 0;
  *(_DWORD *)(a1 + 580) = 0;
  *(_DWORD *)(a1 + 588) = 0;
  *(_DWORD *)(a1 + 596) = 0;
  *(_DWORD *)(a1 + 608) = 0;
}
