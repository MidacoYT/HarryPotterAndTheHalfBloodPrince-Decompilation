
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

#define LOBYTE(x) (*((unsigned char*)&(x)))
#define HIBYTE(x) (*((unsigned char*)&(x)+1))
#define LOWORD(x) (*((unsigned short*)&(x)))
#define HIWORD(x) (*((unsigned short*)&(x)+1))
#define LODWORD(x) (*((unsigned int*)&(x)))
#define HIDWORD(x) (*((unsigned int*)&(x)+1))
#define SLODWORD(x) (*((int*)&(x)))
#define SHIDWORD(x) (*((int*)&(x)+1))
#define BYTE0(x) (*((unsigned char*)&(x)))
#define BYTE1(x) (*((unsigned char*)&(x)+1))
#define BYTE2(x) (*((unsigned char*)&(x)+2))
#define BYTE3(x) (*((unsigned char*)&(x)+3))
#define BYTE4(x) (*((unsigned char*)&(x)+4))
#define BYTE5(x) (*((unsigned char*)&(x)+5))
#define BYTE6(x) (*((unsigned char*)&(x)+6))
#define BYTE7(x) (*((unsigned char*)&(x)+7))
#define BYTE8(x) (*((unsigned char*)&(x)+8))
#define BYTE9(x) (*((unsigned char*)&(x)+9))
#define BYTE10(x) (*((unsigned char*)&(x)+10))
#define BYTE11(x) (*((unsigned char*)&(x)+11))
#define BYTE12(x) (*((unsigned char*)&(x)+12))
#define BYTE13(x) (*((unsigned char*)&(x)+13))
#define BYTE14(x) (*((unsigned char*)&(x)+14))
#define BYTE15(x) (*((unsigned char*)&(x)+15))
#define WORD1(x) (*((unsigned short*)&(x)+1))
#define WORD2(x) (*((unsigned short*)&(x)+2))
#define WORD3(x) (*((unsigned short*)&(x)+3))
#define DWORD1(x) (*((unsigned int*)&(x)+1))
#define DWORD2(x) (*((unsigned int*)&(x)+2))
#define DWORD3(x) (*((unsigned int*)&(x)+3))
#define COERCE_UNSIGNED_INT(x) ((unsigned int)(x))
#define COERCE_FLOAT(x) (*(float*)&(x))
#define COERCE_DOUBLE(x) (*(double*)&(x))
#define __PAIR64__(high, low) (((unsigned __int64)(unsigned int)(high) << 32) | (unsigned int)(low))
#define __PAIR128__(high, low) (low)

extern void fn_006B22C3(void);
extern __int64 fn_006B2359(int a1);
extern int fn_006B2456(int a1, int a2, int a3);

int fn_006B17E5(int a1, int a2)
{
  int v2; // esi

  v2 = fn_006B2456(a1, a2, 0);
  fn_006B22C3(v2);
  return fn_006B2359(v2) != 0;
}
