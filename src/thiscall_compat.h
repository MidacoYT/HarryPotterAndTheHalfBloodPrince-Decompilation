#include "scalar_aliases.h"
#define __thiscall __fastcall
#define HIBYTE(w) ((unsigned char)(((unsigned long)(w) >> 8) & 0xFF))
#define BYTE2(w) ((unsigned char)(((unsigned long)(w) >> 16) & 0xFF))
#define BYTE1(w) ((unsigned char)(((unsigned long)(w) >> 8) & 0xFF))
#define HIWORD(w) ((unsigned short)(((unsigned long)(w) >> 16) & 0xFFFF))
#define LOBYTE(w) (*((unsigned char *)&(w)))
