
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

int fn_006306F0(int a1, int a2, int a3)
{
  if ( *(_DWORD *)(a1 + 4) )
    return *(_DWORD *)(a1 + 4) + *(_DWORD *)(*(_DWORD *)(a1 + 4) + 16) + 12 * (a2 + *(_DWORD *)(a3 + 12));
  else
    return *(_DWORD *)(a3 + 12) + 12 * a2;
}
