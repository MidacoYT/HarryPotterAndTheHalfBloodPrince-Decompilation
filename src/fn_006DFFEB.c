#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_89B1C8;
extern _DWORD dword_89B1CC;
extern _DWORD dword_89B1D0;
int sub_6DFFEB()
{
  int result; // eax
  int v1; // esi

  result = dword_89B1C8;
  if ( dword_89B1C8 != dword_89B1D0 )
  {
    dword_89B1D0 = dword_89B1C8;
    result = dword_89B1CC;
    if ( dword_89B1CC )
    {
      do
      {
        v1 = *(_DWORD *)result;
        (*(void (__cdecl **)(_DWORD))(result + 8))(*(_DWORD *)(result + 12));
        result = v1;
      }
      while ( v1 );
    }
  }
  return result;
}
