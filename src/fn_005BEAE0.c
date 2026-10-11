
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


int fn_005BEAE0(void)
{
  _BYTE *v0; // ecx

  return !*(_BYTE *)((*(int*)0xFCADDC) + 41824)
      && !*(_BYTE *)((*(int*)0xFCADDC) + 41825)
      && !*(_BYTE *)((*(int*)0xFCADDC) + 1248)
      && ((v0 = *(_BYTE **)((*(int*)0xFCADDC) + 1244)) == 0 || (*v0 & 1) == 0)
      && !*(_DWORD *)((*(int*)0xFCADDC) + 1320);
}
