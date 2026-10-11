void fn_006F7040(void)
{
    unsigned int value = *(volatile unsigned int *)0x00FCFA60;
    value &= 0xFFFFFFFEu;
    *(volatile unsigned int *)0x00FCFA60 = value;
}
