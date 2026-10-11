typedef unsigned int u32;
typedef unsigned char u8;

__declspec(noinline) void fn_0062CD20(u32 p, u32 q)
{
    volatile u32 *o = (volatile u32 *)p;
    o[1] = 0;
    o[0] = 0x8427b8;
    o[2] = 1;
    o[3] = *(u32 *)q;
    o[0] = 0x8427d0;
    o[4] = 0xffffffffu;
    o[5] = 0;
    o[6] = 0;
    *(volatile u8 *)(p + 0x1c) = 0;
}
