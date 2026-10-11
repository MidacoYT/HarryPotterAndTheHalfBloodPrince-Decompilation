
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

unsigned int fn_0063B450(unsigned int a1, int * a2, unsigned int * a3, int * a4)
{
  unsigned int result; // eax

  *a2 = a1 & 0xFFFFF;
  *a4 = (a1 >> 20) & 0x3F;
  result = a1 >> 26;
  *a3 = result;
  return result;
}
