struct C { C *__thiscall f(); };
C *C::f() { *(unsigned int *)this=0x0071b628; *(unsigned int *)((char *)this+4)=0; *(unsigned int *)((char *)this+8)=3; *(unsigned int *)((char *)this+0xc)=0; *(unsigned int *)((char *)this+0x10)=0; *(unsigned int *)((char *)this+0x14)=0; return this; }
