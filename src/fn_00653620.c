#include "thiscall_compat.h"

/* PRIVATE inferred compilation candidate. Raw pseudo-C preserved separately. */

// Interface de conteneur (slot partage, pas l'interface de tache) : si !this[8], appelle sub-objet (this[1]) vtable+28, itere les items (count=vtable+16, array=vtable+48) en appelant vtable+4(item) (notify enter), pose this[8]=1. Partagee par les vtables 0x820770/0x82b33c/0x82c2d4/off_843DF8/off_826F38.
void __fastcall fn_00653620(_BYTE *hp6_receiver, void *hp6_unused_edx)
{
  int v2; // edi
  int v3; // ebp
  int *v4; // edi
  int v5; // ecx

  if ( !hp6_receiver[8] )
  {
    (*(void (__thiscall **)(_DWORD))(**((_DWORD **)hp6_receiver + 1) + 28))(*((_DWORD *)hp6_receiver + 1));
    v2 = (*(int (__thiscall **)(_BYTE *))(*(_DWORD *)hp6_receiver + 48))(hp6_receiver);
    v3 = 0;
    if ( (*(int (__thiscall **)(_BYTE *))(*(_DWORD *)hp6_receiver + 16))(hp6_receiver) > 0 )
    {
      v4 = (int *)(v2 + 4);
      do
      {
        v5 = *v4;
        *(v4 - 1) = 0;
        (*(void (__thiscall **)(int))(*(_DWORD *)v5 + 4))(v5);
        ++v3;
        v4 += 2;
      }
      while ( v3 < (*(int (__thiscall **)(_BYTE *))(*(_DWORD *)hp6_receiver + 16))(hp6_receiver) );
    }
    hp6_receiver[8] = 1;
  }
}

