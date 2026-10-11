
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

int fn_004C82F0(int a1)
{
  int result; // eax
  int v2; // ecx

  result = *(&(*(int*)0xD64598) + (*(int*)0x89EB14)) / 3;
  v2 = *(_DWORD *)(**(_DWORD **)(a1 + 344) + 32);
  if ( (v2 & 0x10) != 0 && (v2 & 0x20) != 0 )
  {
    if ( (unsigned int)(result - *(_DWORD *)(a1 + 428)) > 0x1F4 )
      *(_DWORD *)(a1 + 424) = result;
    *(_DWORD *)(a1 + 428) = result;
  }
  return result;
}
