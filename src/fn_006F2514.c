typedef unsigned int u32;
typedef unsigned char u8;

void __fastcall fn_006F2514(u8 *self, void *edx, u32 *out)
{
    u32 a = *(volatile u32 *)(self + 4);
    u32 c;
    u32 b;
    (void)edx;
    out[0] = a;
    c = *(volatile u32 *)(self + 0xD5C);
    b = *(volatile u32 *)(self + 0xD44);
    out[2] = c;
    out[1] = b;
}
