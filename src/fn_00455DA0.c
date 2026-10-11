unsigned char __fastcall fn_00455DA0(unsigned char *self, void *unused) {
    unsigned char flags;
    (void)unused;
    flags = self[4];
    if ((flags & 1) != 0) {
        self[4] = (unsigned char)(flags & 0xFE);
        return 1;
    }
    return 0;
}
