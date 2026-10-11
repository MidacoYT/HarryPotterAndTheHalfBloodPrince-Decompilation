typedef unsigned int u32;
struct S { u32 pad; u32 *p; unsigned char f(); };
__declspec(noinline) unsigned char S::f() { *p = *(volatile u32*)0x00d7a038 + 0x150; return 1; }
