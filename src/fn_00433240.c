
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

int * fn_00433240(int * result)
{
  int v1; // ecx
  int v2; // ecx

  for ( ; *result; *(_DWORD *)(v1 + 148) = 0 )
  {
    v1 = *result;
    *result = *(_DWORD *)(*result + 144);
    *(_DWORD *)(v1 + 144) = 0;
  }
  for ( ; result[1]; *(_DWORD *)(v2 + 148) = 0 )
  {
    v2 = result[1];
    result[1] = *(_DWORD *)(v2 + 144);
    *(_DWORD *)(v2 + 144) = 0;
  }
  *((_BYTE *)result + 16) = 0;
  return result;
}
