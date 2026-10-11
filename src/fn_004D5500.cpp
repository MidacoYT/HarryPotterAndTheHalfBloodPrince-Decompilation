struct B { virtual void a(); virtual void b(); virtual void c(); virtual void d(); }; struct A { unsigned pad; B *p; }; extern "C" __declspec(noinline) void fn_004D5500(A *obj) { obj->p->d(); }
