struct C { void __thiscall f(int value); };
void C::f(int value) { *(int *)((char *)this + 0x10) = value; }

