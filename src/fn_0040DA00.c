
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

int fn_0040DA00(int a1)
{
  int v1; // eax

  v1 = *(_DWORD *)(a1 + 80);
  return v1 == (*(int*)0x89C900)
      || v1 == (*(int*)0x89D7B4)
      || v1 == (*(int*)0x89D108)
      || v1 == (*(int*)0x89D7D0)
      || v1 == (*(int*)0x89D904)
      || v1 == (*(int*)0x89D77C);
}
