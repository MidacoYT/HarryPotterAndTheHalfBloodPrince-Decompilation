int __fastcall fn_0041F140(const unsigned char *self, void *unused) {
    (void)unused;
    if (*(const int *)(self + 0x4c) != 0) {
        int result = *(const int *)(self + 0x18);
        if (self[0x50] == 0) result = *(const int *)(self + 0x44);
        return result;
    }
    return *(const int *)(self + 0x18);
}
