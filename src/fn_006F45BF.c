typedef unsigned int u32;
typedef unsigned char u8;

#pragma optimize("y", off)
void __fastcall fn_006F45BF(u8 **self, void *edx_dummy,
                            u32 index, u32 value0, u32 value1, u32 value2)
{
    u32 *entries = *(u32 **)(*self + 0x28);
    (void)edx_dummy;
    entries[index * 3u - 3u] = value1;
    entries[index * 3u - 2u] = value2;
    entries[index * 3u - 1u] = value0;
}
#pragma optimize("y", on)
