#ifndef HP6_GHIDRA_TYPES_H
#define HP6_GHIDRA_TYPES_H

typedef unsigned char undefined;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned __int64 undefined8;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned char byte;
typedef unsigned int uint3;
typedef void code(void);

#define CONCAT44(hi, lo) (((unsigned __int64)(unsigned int)(hi) << 32) | (unsigned int)(lo))
#define CONCAT22(hi, lo) (((unsigned int)(unsigned short)(hi) << 16) | (unsigned short)(lo))
#define CONCAT13(hi, lo) (((unsigned int)(unsigned char)(hi) << 24) | ((unsigned int)(lo) & 0xFFFFFF))
#define CONCAT31(hi, lo) (((unsigned int)(hi) << 8) | (unsigned char)(lo))
#define SUB84(x, n) ((unsigned int)((unsigned __int64)(x) >> ((n) * 8)))
#define SUB41(x, n) ((unsigned char)((unsigned int)(x) >> ((n) * 8)))
#define SUB42(x, n) ((unsigned short)((unsigned int)(x) >> ((n) * 8)))
#define SUB164(x, n) ((unsigned __int64)(x))

#endif


void fn_006E7226(int param_1)
{

  int iVar1;

  

  iVar1 = param_1 * 0x88 + (*(int*)0x0089B2B8);

  (**(code **)(iVar1 + 0x80))(*(undefined4 *)(iVar1 + 0x68));

  return;

}
