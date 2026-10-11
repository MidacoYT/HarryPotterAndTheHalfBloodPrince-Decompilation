void __fastcall fn_006E83BC(void *self)
{
    unsigned int *words = (unsigned int *)((unsigned char *)self + 0x1C0);
    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
    *((unsigned char *)self + 0x1D4) = 1;
}
