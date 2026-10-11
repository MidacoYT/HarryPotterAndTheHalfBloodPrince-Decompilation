
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


char * fn_006C5170(char * a1)
{
  while ( *a1 != 10 && *a1 != 13 )
    ++a1;
  while ( *a1 == 10 || *a1 == 13 )
    ++a1;
  return a1;
}
