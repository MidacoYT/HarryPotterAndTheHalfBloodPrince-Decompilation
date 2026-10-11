typedef unsigned char u8;
typedef unsigned int u32;
unsigned char fn_00548EB0(void)
{
    u8 *obj = *(u8 **)0x00CEF610;
    int elapsed;
    float scaled;
    if (obj[0xB0] == 0 || obj[0xB2] == 0)
        goto zero;
    elapsed = *(u32 *)0x00D644F8 - *(u32 *)(obj + 0xB4);
    scaled = (float)elapsed * *(float *)0x0084835C;
    if (!(scaled >= *(float *)(obj + 0xA4)))
        goto zero;
    return 1;
zero:
    return 0;
}
