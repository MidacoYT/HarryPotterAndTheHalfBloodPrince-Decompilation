typedef unsigned int _DWORD;

class C_fn_006B62D1 {
public:
  int method(int a2);
};

int C_fn_006B62D1::method(int a2)
{
  int this_ = (int)this;
  int v2; // edx
  int v4; // [esp-4h] [ebp-4h]

  *(_DWORD *)(this_ + 116) = a2;
  v2 = 0;
  switch ( a2 )
  {
    case 1:
      v4 = 10;
      goto LABEL_9;
    case 2:
      v4 = 11;
      goto LABEL_9;
    case 3:
      v4 = 12;
      goto LABEL_9;
    case 4:
      v4 = 13;
LABEL_9:
      v2 = v4;
      break;
  }
  return (*(int (__thiscall **)(_DWORD, int, _DWORD))(**(_DWORD **)(this_ + 20) + 84))(*(_DWORD *)(this_ + 20), v2, 0);
}
