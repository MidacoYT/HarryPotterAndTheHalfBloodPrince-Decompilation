#pragma optimize("y", off)
#pragma optimize("s", on)
void __fastcall fn_006F45E6(void **self, void *edx_unused, int first, int second)
{
    volatile int *object = (volatile int *)*self;
    volatile int *second_source = &second;
    object[0x50 / 4] = first;
    object[0x54 / 4] = *second_source;
}
#pragma optimize("y", on)
