#include "thiscall_compat.h"
extern _DWORD unk_85303E;
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _BYTE byte_89B294;
int __cdecl sub_6EA783(int a1)
{
  int result; // eax

  for ( result = 0; result < 6; ++result )
  {
    if ( a1 == *((char *)&unk_85303E + 6 * (unsigned __int8)byte_89B294 + result) )
      break;
  }
  return result;
}
