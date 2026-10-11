class C_fn_00691EC0 {
public:
  int * method(int a2, int a3, int a4);
};
__declspec(noinline) int * C_fn_00691EC0::method(int a2, int a3, int a4) { return 0; }

int * fn_00691F00(int **a1, int a2, int a3, int a4)
{
  if ( *a1 )
    return ((C_fn_00691EC0*)(*a1))->method(a2, a3, a4);
  else
    return 0;
}
