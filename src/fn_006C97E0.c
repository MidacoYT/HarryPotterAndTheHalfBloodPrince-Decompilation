#pragma optimize("y", off)

typedef unsigned int u32;
typedef unsigned char u8;

void fn_006C97E0(u8 *self, u32 condition, u32 *out_value)
{
    if (*(volatile u32 *)&condition == 0)
        *out_value = *(u32 *)(self + 0x1a0);
}

#pragma optimize("y", on)
