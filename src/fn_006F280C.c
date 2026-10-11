void __fastcall fn_006F280C(void *self, void *edx_unused, volatile float *target)
{
    volatile float *destination = *(volatile float * volatile *)&target;
    volatile float *source = (volatile float *)((unsigned char *)self + 0x98);
    (void)edx_unused;
    destination[0] = source[0];
    destination[1] = source[1];
}


