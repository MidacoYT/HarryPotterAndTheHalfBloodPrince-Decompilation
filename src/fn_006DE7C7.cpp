struct C { C *__thiscall f(); };
C *C::f() { *(unsigned *)this = 0x71b670; return this; }
