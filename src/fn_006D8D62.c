typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;
typedef unsigned __int64 _QWORD;
typedef int BOOL;
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;

extern void fn_006D8C7D(int, int *);

int fn_006D8D62(int a1, int a2, int a3)
{
  int v4[3]; // [esp+0h] [ebp-Ch] BYREF

  fn_006D8C7D(a1, v4);
  return a3 * a2 / (v4[0] * v4[1]);
}
