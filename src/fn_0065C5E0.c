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

int * __fastcall fn_0065C5E0(int a1, int a2)
{
  int *result; // eax
  int v3; // ecx

  result = (int *)(*(int*)0xCE9F2C);
  if ( !(*(int*)0xCE9F2C) )
    return 0;
  while ( 1 )
  {
    v3 = a2 - result[260];
    if ( v3 < result[258] && v3 >= 0 )
      break;
    result = (int *)result[261];
    if ( !result )
      return 0;
  }
  return result;
}
