
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

int * fn_006205D0(int * result, int a2)
{
  int v2; // edx

  if ( result )
  {
    v2 = *(_DWORD *)(a2 + 1608);
    if ( v2 )
      *(_DWORD *)(v2 + 388) = result;
    result[96] = *(_DWORD *)(a2 + 1608);
    result[97] = 0;
    *(_DWORD *)(a2 + 1608) = result;
  }
  result[98] = a2;
  result[42] = result;
  result[43] = 0;
  result[44] = a2 + 384;
  return result;
}
