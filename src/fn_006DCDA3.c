#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __stdcall sub_6DCCAD(int a1, int a2);
int __fastcall sub_6DCDA3(_DWORD **this, void *hp6_unused_edx)
{
  (*(void (__stdcall **)(_DWORD *, _DWORD, int (__stdcall *)(int, int), _DWORD **, int))(*this[45] + 16))(
    this[45],
    0,
    sub_6DCCAD,
    this,
    1);
  return 0;
}
