#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern int __cdecl sub_6E7828(unsigned __int8 *a1, int a2);
int __cdecl sub_6E81E4(unsigned __int8 **a1)
{
  unsigned __int8 *v1; // eax
  unsigned __int8 *v2; // ecx
  unsigned __int8 *v4; // eax
  unsigned __int8 *v5; // ecx
  int v6; // eax
  unsigned int v7; // ecx
  unsigned __int8 *v8; // eax

  while ( 1 )
  {
    v1 = *a1;
    if ( **a1 != 0xFC )
      break;
    ++*a1;
  }
  v2 = (unsigned __int8 *)*v1;
  a1[1] = v2;
  if ( v2 == (unsigned __int8 *)255 )
    return 0;
  v4 = v1 + 1;
  *a1 = v4;
  if ( v2 != (unsigned __int8 *)253 && v2 != (unsigned __int8 *)254 )
  {
    v5 = (unsigned __int8 *)*v4;
    a1[4] = v5;
    if ( v5 == (unsigned __int8 *)255 )
    {
      v6 = sub_6E7828(v4 + 1, 4);
      *a1 += 4;
      a1[4] = (unsigned __int8 *)v6;
    }
    ++*a1;
    v7 = (unsigned int)a1[4];
    v8 = *a1;
    a1[3] = *a1;
    if ( v7 <= 4 )
      a1[2] = (unsigned __int8 *)sub_6E7828(v8, v7);
    *a1 = &(*a1)[(_DWORD)a1[4]];
  }
  return 1;
}
