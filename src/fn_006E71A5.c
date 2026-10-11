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


void fn_006E71A5(int *param_1,int *param_2)
{

  if (param_2 == (int *)*param_1) {

    *param_1 = *(int *)*param_1;

  }

  if (param_2 == (int *)param_1[1]) {

    param_1[1] = ((int *)param_1[1])[1];

  }

  if ((int *)param_2[1] != (int *)0x0) {

    *(int *)param_2[1] = *param_2;

  }

  if (*param_2 != 0) {

    *(int *)(*param_2 + 4) = param_2[1];

  }

  param_1[2] = param_1[2] + -1;

  return;

}
