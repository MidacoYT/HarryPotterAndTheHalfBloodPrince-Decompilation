int __cdecl fn_00404FC0(void) {
    int index = *(volatile int *)0x0089eb14;
    int value = *(volatile int *)(0x00d64598 + index * 4);
    return value / 3;
}
