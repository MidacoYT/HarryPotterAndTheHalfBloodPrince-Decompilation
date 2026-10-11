typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;

class C_fn_006B2C65 {
public:
  int method(int a2);
};

int C_fn_006B2C65::method(int a2)
{
  int *this_ = (int *)this;
  int v2; // edx
  int result; // eax

  if ( *this_ )
    v2 = *this_ + 8;
  else
    v2 = 0;
  result = a2;
  *(_DWORD *)(a2 + 8) = v2;
  ++this_[2];
  *this_ = a2;
  if ( !*(_DWORD *)(a2 + 8) )
    this_[1] = a2;
  return result;
}
