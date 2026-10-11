typedef unsigned int u32;
struct S { u32 pad; float value; unsigned char f(); };
__declspec(noinline) unsigned char S::f() { *(float*)((char*)*(volatile u32*)0x00d7a038 + 0xf4) = value; return 1; }
