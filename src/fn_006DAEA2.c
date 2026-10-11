#pragma optimize("y", off)
typedef unsigned char u8;
typedef unsigned int u32;
unsigned long long __fastcall fn_006DAEA2(void *object, int unused, int index) {
    u8 *base = *(u8 **)((u8 *)object + 0x1c);
    u32 offset = (u32)index << 5;
    (void)unused;
    return *(volatile unsigned long long *)(offset + (u32)base + 0x18);
}
#pragma optimize("y", on)
