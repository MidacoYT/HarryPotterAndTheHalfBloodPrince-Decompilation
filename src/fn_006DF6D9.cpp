struct D { unsigned char pad[0x4c]; volatile int a; volatile int b; };
int fn_006DF6D9(int index)
{
    if (*(unsigned char *)0x0089b438 == 0)
        return -10;
    D *p = *(D **)(0x0089b144 + index * 4);
    if (p == 0)
        return -1;
    return p->a + p->b;
}
