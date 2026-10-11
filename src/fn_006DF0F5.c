#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B4A4;
int __cdecl sub_6DF0F5(int a1, int a2)
{
  int result; // eax
  int v3; // esi
  int v4; // edi
  __int16 *v5; // edx

  result = -1;
  v3 = 0;
  v4 = -1;
  if ( a2 > 0 )
  {
    v5 = (__int16 *)(144 * a1 + dword_89B4A4 + 4);
    do
    {
      if ( *v5 > v4 )
      {
        v4 = *v5;
        result = v3;
      }
      ++v3;
      ++v5;
    }
    while ( v3 < a2 );
  }
  return result;
}
