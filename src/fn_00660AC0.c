
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

int fn_00660AC0(int a1, unsigned int a2)
{
  int result; // eax
  unsigned int i; // ecx

  result = *(_DWORD *)(a1 + 56);
  for ( i = 0; result; ++i )
  {
    if ( i >= a2 )
      break;
    result = *(_DWORD *)(result + 732);
  }
  return result;
}
