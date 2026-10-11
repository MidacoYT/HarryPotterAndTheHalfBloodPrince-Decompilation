int fn_0066A750(void)
{
    int eax, ecx, edx, esi;
    edx = 0;
    L_66A753:;
    ecx = (unsigned short)(((unsigned short)edx));
    eax = ecx;
    ecx = ecx & (0x1f);
    esi = 1;
    esi = ((unsigned int)(esi)) << (((unsigned char)ecx));
    eax = ((unsigned int)(eax)) >> (5);
    eax = (int)((eax) * 4 + 0xce9388);
    edx = edx + (1);
    esi = ~(esi);
    *(int*)(eax) = *(int*)(eax) & (esi);
    if (((unsigned int)(edx)) < ((unsigned int)(0x2000))) goto L_66A753;
    return eax;
}
