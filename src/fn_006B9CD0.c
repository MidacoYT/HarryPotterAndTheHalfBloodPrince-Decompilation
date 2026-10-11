int __cdecl fn_006B9CD0(const unsigned char *base) {
    unsigned int off;
    const unsigned char *nt;
    if (*(const unsigned short *)base != 0x5a4d) return 0;
    off = *(const unsigned int *)(base + 0x3c);
    nt = base + off;
    if (*(const unsigned int *)nt != 0x4550) return 0;
    return *(const unsigned short *)(nt + 0x18) == 0x10b;
}
