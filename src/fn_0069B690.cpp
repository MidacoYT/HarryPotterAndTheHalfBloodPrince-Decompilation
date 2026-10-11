class C_fn_0069B620 {
public:
  int * method(int a2, int a3, int a4);
};
__declspec(noinline) int * C_fn_0069B620::method(int a2, int a3, int a4) { return 0; }

int * fn_0069B690(int **a1, int a2, int a3)
{
  if ( *a1 )
    return ((C_fn_0069B620*)(*a1))->method(a2, a3, a3);
  else
    return 0;
}
