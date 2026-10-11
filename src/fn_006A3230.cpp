class C_fn_006A31E0 {
public:
  float * method(float * a2);
};
__declspec(noinline) float * C_fn_006A31E0::method(float * a2) { return 0; }

float * fn_006A3230(float **a1, float *a2)
{
  if ( *a1 )
    return ((C_fn_006A31E0*)(*a1))->method(a2);
  else
    return 0;
}
