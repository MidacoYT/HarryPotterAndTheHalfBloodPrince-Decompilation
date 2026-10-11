char __fastcall fn_00631CB0(void *self)
{
    unsigned int base = *(volatile unsigned int *)0x00D7A038;
    unsigned int *destination = *(unsigned int **)(base + 0x10C);
    * (unsigned int *)((unsigned char *)destination + 0x2504) =
        *(unsigned int *)((unsigned char *)self + 4);
    return 1;
}
