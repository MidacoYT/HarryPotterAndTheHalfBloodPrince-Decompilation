
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


int __fastcall fn_006F2478(int this)
{
  int result; // eax

  result = this;
  *(_DWORD *)(this + 3396) = 0;
  *(_DWORD *)(this + 3412) = 0;
  *(_DWORD *)(this + 3416) = 0;
  *(_WORD *)(this + 3408) = 0;
  *(_WORD *)(this + 3410) = 0;
  *(_DWORD *)(this + 3420) = 0;
  *(_DWORD *)(this + 3424) = 0;
  *(_DWORD *)(this + 3428) = 1;
  return result;
}
