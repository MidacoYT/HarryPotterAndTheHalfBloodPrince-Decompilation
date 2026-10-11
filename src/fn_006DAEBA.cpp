typedef unsigned long long u64;
struct C { u64 __thiscall f(int index); };
u64 C::f(int index) {
    char *entry = *(char **)((char *)this + 0x1c) + index * 0x20;
    char *object = *(char **)(entry + 8);
    return *(u64 *)(object + 0x110) + *(u64 *)(entry + 0x10);
}
