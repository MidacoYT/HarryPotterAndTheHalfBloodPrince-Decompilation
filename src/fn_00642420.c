#include "thiscall_compat.h"
/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */
extern _DWORD dword_CF19BC;
extern int sub_6525D0();
int sub_642420()
{
  int result; // eax

  result = sub_6525D0();
  if ( (unsigned int)dword_CF19BC >= 3 )
    return sub_6532E0();
  return result;
}
