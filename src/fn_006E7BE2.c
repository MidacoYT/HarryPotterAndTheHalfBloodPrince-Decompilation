
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

extern float * fn_006E7B18(int a1, int a2, int a3, float * a4);

int fn_006E7BE2(int a1, int a2, int a3, float * a4)
{
  int (__cdecl **v5)(int, int, float *, int, int); // eax
  int result; // eax
  int v7; // ebx
  int v8; // edi
  int v9; // edi
  float *v10; // [esp+8h] [ebp-4h]
  int v11; // [esp+14h] [ebp+8h]

  v5 = *(int (__cdecl ***)(int, int, float *, int, int))(a1 + 8);
  if ( !v5 || (result = (*v5)(v5, a2, a4, a3, *(unsigned __int8 *)(a1 + 26)), result > 0) )
  {
    v7 = a2;
    v11 = a3;
    v10 = a4;
    while ( v7 > 0 )
    {
      v8 = *(int *)(a1 + 40);
      if ( *(int *)(a1 + 36) >= v8 )
        *(int *)(a1 + 36) = 0;
      v9 = v8 - *(int *)(a1 + 36);
      if ( v9 > v7 )
        v9 = v7;
      fn_006E7B18(a1, v9, v11, v10);
      *(int *)(a1 + 36) += v9;
      v11 += 4 * v9;
      v7 -= v9;
      v10 += v9;
    }
    return a2;
  }
  return result;
}
