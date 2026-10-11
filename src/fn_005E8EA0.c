void fn_005E8EA0(void)
{
    unsigned int value = *(volatile unsigned int *)0x0096b48c;
    value = (value + 0x3fu) & 0xffffffc0u;
    *(volatile unsigned int *)0x0096b48c = value;
}
