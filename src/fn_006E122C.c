typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;
typedef unsigned __int64 _QWORD;
typedef int BOOL;

#define LOWORD(x) (*((unsigned short*)&(x)))

extern int fn_006E11E1(int a1);
extern int fn_006E6250(double * a1, int a2);

int fn_006E122C(short * a1)
{
  int result; // eax

  fn_006E6250(a1, 12);
  LOWORD(result) = fn_006E11E1(4);
  *a1 = result;
  return (unsigned __int16)result;
}
