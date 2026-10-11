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


void __fastcall fn_005D0F40(int param_1)
{

  undefined1 *puVar1;

  int iVar2;

  

  iVar2 = 0;

  if (0 < *(int *)(param_1 + 0x10)) {

    puVar1 = (undefined1 *)(param_1 + 0x75);

    do {

      *puVar1 = 0;

      if (*(int *)(puVar1 + -0x39) != 0) {

        *puVar1 = *(int *)(param_1 + 0x20) == *(int *)(puVar1 + -0x39);

      }

      iVar2 = iVar2 + 1;

      puVar1 = puVar1 + 0x50;

    } while (iVar2 < *(int *)(param_1 + 0x10));

    *(undefined1 *)(param_1 + 0x5d2) = *(undefined1 *)(param_1 + 0x620);

    return;

  }

  *(undefined1 *)(param_1 + 0x5d2) = *(undefined1 *)(param_1 + 0x620);

  return;

}
