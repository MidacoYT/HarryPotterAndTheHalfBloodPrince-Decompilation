#pragma optimize("s", on)
#pragma optimize("y", off)
void __fastcall fn_006D6BCE(unsigned int *self, void *unused, int value)
{
    volatile unsigned int *field = (volatile unsigned int *)self;
    volatile int *argument = &value;
    unsigned int flags;
    unsigned int bits;
    int adjusted;

    (void)unused;
    flags = *field & 0xFFFFFBFFu;
    adjusted = *argument;
    --adjusted;
    bits = (adjusted ? 0u : 4u) << 8;
    flags |= bits;
    *field = flags;
}
#pragma optimize("y", on)
#pragma optimize("s", off)

