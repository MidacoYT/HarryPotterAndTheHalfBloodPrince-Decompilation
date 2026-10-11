typedef unsigned int u32;
struct V { virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5(); };
extern "C" __declspec(noinline) u32 __fastcall fn_0062B350(V *p, u32 unused) { u32 count = --*(u32*)((char*)p + 8); if (count == 0) { p->f5(); return 0; } return count; }
