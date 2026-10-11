typedef unsigned int u32; typedef unsigned char u8;
class C1 { public: C1(); };
C1::C1() {
    *(u32*)((u8*)this+4)=0; *(u32*)((u8*)this+8)=0;
    *(u32*)((u8*)this+12)=0; *(u32*)((u8*)this+16)=0;
    *(u32*)this=0x008202ec;
}
