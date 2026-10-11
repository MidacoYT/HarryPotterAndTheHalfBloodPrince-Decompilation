int __cdecl fn_006E0778(int index) {
    unsigned char count = *(volatile unsigned char *)0x89b2fe;
    if (index >= count || index < 0) return 0;
    return *(int *)(0x89b200 + index * 4);
}
