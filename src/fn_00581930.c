int __fastcall fn_00581930(int index) {
    int base = *(volatile int *)0x00D46AA8;
    if (base != 0) {
        return *(int *)(base + index * 4 + 0xA8);
    }
    return 0;
}
