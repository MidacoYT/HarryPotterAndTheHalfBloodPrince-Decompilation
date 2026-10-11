#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern const char *__cdecl sub_6DC751(int a1, char *a2, int a3, int *a4, int *a5);
int __cdecl sub_6DC86F(int a1, char *a2)
{
  int v3; // [esp+0h] [ebp-4h] BYREF

  v3 = 0;
  if ( a2 )
    sub_6DC751(a1, a2, 0, &v3, 0);
  return v3;
}
