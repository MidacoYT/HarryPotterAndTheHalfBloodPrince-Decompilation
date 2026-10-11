struct C { C *__thiscall f(); };
C *C::f() { *(unsigned int *)this = 0x00717134; *(int *)((char *)this+4)=0; *(int *)((char *)this+8)=0; *(int *)((char *)this+0x0c)=0; return this; }
