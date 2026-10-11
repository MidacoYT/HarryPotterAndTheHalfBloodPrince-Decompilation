int fn_006E0A12(void)
{
    int eax, ecx, edx;
    ecx = (unsigned char)(*(unsigned char*)(0x89b2fe));
    eax = 0;
    edx = 0;
    if (((int)(ecx)) <= ((int)(0))) goto L_6E0A31;
    L_6E0A21:;
    if ((*(int*)((edx) * 4 + 0x89b200)) == (0)) goto L_6E0A2C;
    eax = eax + 1;
    L_6E0A2C:;
    edx = edx + 1;
    if (((int)(edx)) < ((int)(ecx))) goto L_6E0A21;
    L_6E0A31:;
    return eax;
}
