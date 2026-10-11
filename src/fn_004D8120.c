void __fastcall fn_004D8120(unsigned int *p)
{
    p[0x58/4] = 0;
    p[0x5c/4] = 0;
    p[0x60/4] = 0;
    p[0x54/4] = 0;
    p[0x50/4] = 0x00820278;
    p[0x68/4] = 0x00820278;
    p[0x70/4] = 0;
    p[0x74/4] = 0;
    p[0x78/4] = 0;
    p[0x6c/4] = 0;
}
int __cdecl fn_004DA3D0(void)
{
    return *(volatile unsigned char *)0x00CEF54F ||
           *(volatile unsigned char *)0x00CEF558 ||
           *(volatile unsigned int *)0x00CEF55C;
}
