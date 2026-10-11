typedef unsigned int u32; typedef unsigned char u8;
class C { public: C(); };
C::C() { *(u32*)((u8*)this+4)=0x00820278; *(u32*)((u8*)this+0x0c)=0; *(u32*)((u8*)this+0x10)=0; *(u32*)((u8*)this+0x14)=0; *(u32*)((u8*)this+8)=0; }