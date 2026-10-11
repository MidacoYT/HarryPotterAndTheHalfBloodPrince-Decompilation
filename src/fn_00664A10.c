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

void fn_00664A10(int reg_arg)
{


  

  if (reg_arg != 0) {

    if (*(int *)(reg_arg + 0x10) != 0) {

      *(int *)(reg_arg + 0x10) = *(int *)(reg_arg + 0x10) + reg_arg;

    }

    if (*(int *)(reg_arg + 0x14) != 0) {

      *(int *)(reg_arg + 0x14) = *(int *)(reg_arg + 0x14) + reg_arg;

    }

    if (*(int *)(reg_arg + 0x18) != 0) {

      *(int *)(reg_arg + 0x18) = *(int *)(reg_arg + 0x18) + reg_arg;

    }

    if (*(int *)(reg_arg + 0x48) != 0) {

      *(int *)(reg_arg + 0x48) = *(int *)(reg_arg + 0x48) + reg_arg;

    }

    if (*(int *)(reg_arg + 0x60) != 0) {

      *(int *)(reg_arg + 0x60) = *(int *)(reg_arg + 0x60) + reg_arg;

    }

    if (*(int *)(reg_arg + 100) != 0) {

      *(int *)(reg_arg + 100) = *(int *)(reg_arg + 100) + reg_arg;

    }

    if (*(int *)(reg_arg + 0x68) != 0) {

      *(int *)(reg_arg + 0x68) = *(int *)(reg_arg + 0x68) + reg_arg;

    }

    if (*(int *)(reg_arg + 0x6c) != 0) {

      *(int *)(reg_arg + 0x6c) = *(int *)(reg_arg + 0x6c) + reg_arg;

    }

    if (*(int *)(reg_arg + 0x70) != 0) {

      *(int *)(reg_arg + 0x70) = *(int *)(reg_arg + 0x70) + reg_arg;

    }

  }

  return;

}
