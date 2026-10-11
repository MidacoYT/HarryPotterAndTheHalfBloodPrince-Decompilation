
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

unsigned int fn_005F2710(unsigned int a1, unsigned int * a2)
{
  unsigned int result; // eax
  unsigned int v3; // ecx

  result = *a2;
  v3 = 0;
  if ( !*a2 )
    goto LABEL_6;
  do
  {
    if ( result > a1 )
      break;
    v3 = result;
    result = *(_DWORD *)(result + 144);
  }
  while ( result );
  if ( v3 )
  {
    *(_DWORD *)(v3 + 144) = a1;
    *(_DWORD *)(a1 + 144) = result;
  }
  else
  {
LABEL_6:
    *a2 = a1;
    *(_DWORD *)(a1 + 144) = result;
  }
  return result;
}
