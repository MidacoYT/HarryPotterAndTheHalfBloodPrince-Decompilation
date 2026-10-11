class C_fn_006E86AA {
public:
  unsigned int method(int a2);
};
__declspec(noinline) unsigned int C_fn_006E86AA::method(int a2) { return 0; }

class C_fn_006E86F5 {
public:
  unsigned int method(int a2);
};

unsigned int C_fn_006E86F5::method(int a2)
{
  int *this_ = (int *)this;

  if ( !( a2 ) )
  { return 0; }
  else
  { return ((C_fn_006E86AA*)(this_))->method(a2); }
}
