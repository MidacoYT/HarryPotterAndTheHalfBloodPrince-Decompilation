struct C { C *__thiscall f(); };
C *C::f() { *(unsigned *)this = 0; return this; }
