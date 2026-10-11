int __cdecl fn_006F3E5A(void *a, unsigned int value,
                         void *c, void *d, void *e, void *f,
                         unsigned int *out) {
    if (value >= 0x800) {
        *out = 0x800;
        return 1;
    }
    return 0;
}
