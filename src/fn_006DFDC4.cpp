struct D { unsigned pad0,pad1,a,pad3,b; };
int fn_006DFDC4(void)
{
    if (*(unsigned char *)0x0089b438 == 0)
        return -10;
    D *p = *(D **)0x0089b4ac;
    return ((int)p->a - (int)p->b) * 100 / (int)p->a;
}
