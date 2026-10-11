void *memcpy(void *dst, const void *src, unsigned int count);
#pragma intrinsic(memcpy)
void __fastcall fn_00414170(void *self, void *unused, const void *source) {
    (void)unused;
    memcpy((char *)self + 0x90, source, 0xC0);
}
