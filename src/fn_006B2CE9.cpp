typedef unsigned int _DWORD;

class C_fn_006B2C65 {
public:
  int method(int a2);
};
__declspec(noinline) int C_fn_006B2C65::method(int a2) { return 0; }

class C_fn_006B2CE9 {
public:
  int method(int a2, int a3);
};

int C_fn_006B2CE9::method(int a2, int a3)
{
  int *this_ = (int *)this;
  int result; // eax

  if ( !a2 )
    return ((C_fn_006B2C65*)(this_))->method(a3);
  if ( !*(_DWORD *)(a2 + 8) )
    this_[1] = a3;
  result = a3 + 8;
  *(_DWORD *)(a3 + 8) = *(_DWORD *)(a2 + 8);
  *(_DWORD *)(a2 + 8) = a3 + 8;
  ++this_[2];
  return result;
}
