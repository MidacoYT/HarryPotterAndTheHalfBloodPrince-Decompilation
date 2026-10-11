/* Exact scalar aliases only. No fabricated globals, classes or callbacks. */
typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned long _DWORD;
typedef unsigned __int64 _QWORD;
typedef char _SBYTE;
typedef short _SWORD;
typedef long _SDWORD;
typedef __int64 _SQWORD;
typedef unsigned char _BOOL1;
typedef unsigned short _BOOL2;
typedef unsigned long _BOOL4;
typedef unsigned __int64 _BOOL8;
typedef char hp6_assert_dword[(sizeof(_DWORD)==4)?1:-1];

typedef unsigned char bool;
#define true 1
#define false 0
