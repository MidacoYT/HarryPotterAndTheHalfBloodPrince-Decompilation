int fn_006E483E(void)
{
    int eax, ecx, edx, local_4h;
    ecx = (unsigned short)(*(unsigned short*)(0x89b2e4));
    eax = 0;
    if (((int)(ecx)) <= ((int)(0))) goto L_6E485C;
    L_6E484B:;
    edx = *(int*)(0x89b4a8);
    if ((*(int*)(edx + eax * 8)) == (0)) goto L_6E485F;
    eax = eax + 1;
    if (((int)(eax)) < ((int)(ecx))) goto L_6E484B;
    L_6E485C:;
    local_4h = -9;
    eax = local_4h;
    L_6E485F:;
    return eax;
}
