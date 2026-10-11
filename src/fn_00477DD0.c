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


int __fastcall fn_00477DD0(int param_1)
{

  int iVar1;

  

  iVar1 = 0;

  if ((*(int *)(param_1 + 0x1c8) != 0) && (*(char *)(param_1 + 0x1dc) == '\0')) {

    iVar1 = 1;

  }

  if ((*(int *)(param_1 + 0x1e8) != 0) && (*(char *)(param_1 + 0x1fc) == '\0')) {

    iVar1 = iVar1 + 1;

  }

  if ((*(int *)(param_1 + 0x208) != 0) && (*(char *)(param_1 + 0x21c) == '\0')) {

    iVar1 = iVar1 + 1;

  }

  if ((*(int *)(param_1 + 0x228) != 0) && (*(char *)(param_1 + 0x23c) == '\0')) {

    iVar1 = iVar1 + 1;

  }

  if ((*(int *)(param_1 + 0x248) != 0) && (*(char *)(param_1 + 0x25c) == '\0')) {

    iVar1 = iVar1 + 1;

  }

  return iVar1;

}
