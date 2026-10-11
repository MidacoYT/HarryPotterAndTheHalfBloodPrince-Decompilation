struct C { int __thiscall f(int value); };
int C::f(int value) { value++; return *(int *)((char *)this + 0x0c); }
