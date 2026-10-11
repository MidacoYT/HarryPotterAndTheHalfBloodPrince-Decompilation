
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

int fn_00657850(char * a1, char * a2)
{
  int v3; // eax
  int v4; // ecx

  do
  {
    v3 = *a2;
    v4 = *a1;
    ++a2;
    ++a1;
    if ( v3 != v4 )
    {
      if ( (unsigned int)(v3 - 65) <= 0x19 )
        v3 += 32;
      if ( (unsigned int)(v4 - 65) <= 0x19 )
        v4 += 32;
      if ( v3 != v4 )
        break;
    }
  }
  while ( v3 );
  return v3 - v4;
}
