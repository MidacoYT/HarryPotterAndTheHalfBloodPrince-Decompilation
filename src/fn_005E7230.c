#pragma intrinsic(__rdtsc)
unsigned __int64 __rdtsc(void);
void __fastcall fn_005E7230(void *self, void *unused)
{
    unsigned int delta = (unsigned int)__rdtsc() - *(unsigned int *)self;
    (void)unused;
    *(volatile unsigned int *)((char *)self + 4) = delta;
    *(volatile float *)((char *)self + 8) = (float)(int)delta * *(float *)((char *)self + 0x18);
}
