
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

int fn_00623D90(int * a1, int a2)
{
  int result; // eax

  (*(int*)0xD70D4C) = *a1;
  result = a2 + *a1 / 3;
  (*(int*)0xD70D48) = 3 * result;
  return result;
}
