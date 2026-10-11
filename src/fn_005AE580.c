typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;

extern int __fastcall fn_005AE520(int this);

int fn_005AE580(int this, int result)
{
  if ( !( result <= 0 ) )
  {
    *(_DWORD *)(this + 412) += result;
    *(_BYTE *)(this + 428) = 1;
  }
  else
  {
    *(_BYTE *)(this + 429) = 1;
    return fn_005AE520(this);
  }

  return result;
}
