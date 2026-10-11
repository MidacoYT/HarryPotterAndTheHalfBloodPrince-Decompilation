typedef unsigned char u8;
typedef unsigned int u32;
int fn_00582110(void)
{
    u8 *manager = *(u8 **)0x00FCADDC;
    u8 *object;
    if (manager[0x4E0])
        return 1;
    object = *(u8 **)(manager + 0x4DC);
    if (object && (object[0] & 1))
        return 1;
    return *(u32 *)(manager + 0x528) != 0 || *(u32 *)0x00FCAED4 != 0;
}
