
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

int fn_00689D20(int result, int a2)
{
  if ( a2 )
    return (*(int (__cdecl **)(_DWORD, _DWORD, int))(*(_DWORD *)(result + 52) + 16))(
             *(_DWORD *)(result + 52),
             *(_DWORD *)(*(_DWORD *)(result + 52) + 8),
             a2);
  return result;
}
