typedef unsigned int u32; typedef unsigned char u8;
class C { public: C(); };
C::C() { volatile u32 *p=(volatile u32*)this; p[0x58/4]=0;p[0x5c/4]=0;p[0x60/4]=0;p[0x54/4]=0;p[0x50/4]=0x00820278;p[0x68/4]=0x00820278;p[0x70/4]=0;p[0x74/4]=0;p[0x78/4]=0;p[0x6c/4]=0; }