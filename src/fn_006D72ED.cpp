class C_fn_006D72ED {
public:
  unsigned int method(int a2);
};

unsigned int C_fn_006D72ED::method(int a2)
{
  unsigned int *this_ = (unsigned int *)this;
  unsigned int result; // eax

  result = *this_ & 0xFFDFFFFF;
  *this_ = result | ((a2 != 1 ? 0 : 0x2000) << 8);
  return result;
}
