#pragma optimize("s", on)
#pragma optimize("y", off)
void __fastcall fn_006D71FD(unsigned int *self, void *unused, int value)
{
    volatile unsigned int *field = (volatile unsigned int *)self;
    volatile int *argument = &value;
    unsigned int flags;
    unsigned int bits;
    int adjusted;

    (void)unused;
    flags = *field & 0xFFFFF7FFu;
    adjusted = *argument;
    --adjusted;
    bits = (adjusted ? 0u : 8u) << 8;
    flags |= bits;
    *field = flags;
}
#pragma optimize("y", on)
#pragma optimize("s", off)

