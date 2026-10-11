typedef unsigned int u32; typedef unsigned char u8;
class C { public: C(); };
C::C() {
    *(u32*)((u8*)this + 0x4) = 0;
    *(u32*)((u8*)this + 0x0) = 0x008204b4u;
    *(u32*)((u8*)this + 0x8) = 0;
    *(u32*)((u8*)this + 0xc) = 0;
    *(u32*)((u8*)this + 0x10) = 0;
    *(u32*)((u8*)this + 0x14) = 0;
    *(u32*)((u8*)this + 0x18) = 0;
    *(u32*)((u8*)this + 0x1c) = 0;
    *(u32*)((u8*)this + 0x20) = 0;
    *(u32*)((u8*)this + 0x24) = 0;
}
