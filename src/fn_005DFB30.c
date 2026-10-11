
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

int fn_005DFB30(int result, int a2)
{
  _DWORD *v2; // edx

  if ( *(_DWORD *)a2 == a2 )
  {
    *(_DWORD *)(result + 4) = result;
    *(_DWORD *)result = result;
  }
  else
  {
    *(_DWORD *)result = *(_DWORD *)a2;
    v2 = *(_DWORD **)(a2 + 4);
    *(_DWORD *)(result + 4) = v2;
    *v2 = result;
    *(_DWORD *)(*(_DWORD *)result + 4) = result;
  }
  *(_DWORD *)(result + 8) = *(_DWORD *)(a2 + 8);
  *(_DWORD *)(result + 12) = *(_DWORD *)(a2 + 12);
  *(_WORD *)(result + 16) = *(_WORD *)(a2 + 16);
  *(_BYTE *)(result + 18) = *(_BYTE *)(a2 + 18);
  *(_BYTE *)(result + 19) = *(_BYTE *)(a2 + 19);
  return result;
}
