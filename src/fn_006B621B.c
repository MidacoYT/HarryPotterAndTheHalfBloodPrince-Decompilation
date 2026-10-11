
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

extern int __fastcall fn_006B47A4(int * this);
extern int __fastcall fn_006B4996(int * this);

int * __fastcall fn_006B621B(int * this)
{
  fn_006B47A4(this + 2);
  fn_006B4996(this);
  return this;
}
