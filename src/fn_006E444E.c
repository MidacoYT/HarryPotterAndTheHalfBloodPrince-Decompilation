int fn_006E444E(int arg0)
{
    int eax, ecx, edx, local_4h;
    edx = *(int*)((int)&arg0);
    if (((int)(edx)) < ((int)(0))) goto L_6E4480;
    ecx = (signed short)(*(unsigned short*)(0x89b43c));
    eax = edx;
    eax = eax & (0xff);
    if (((int)(eax)) >= ((int)(ecx))) goto L_6E4480;
    ecx = eax;
    ecx = ((int)(ecx)) * (0x90);
    ecx = ecx + (*(int*)(0x89b4a4));
    if ((*(unsigned char*)(ecx + 0x6d)) == (0)) goto L_6E4480;
    if ((*(int*)(ecx)) == (edx)) goto L_6E4483;
    L_6E4480:;
    local_4h = -8;
    eax = local_4h;
    L_6E4483:;
    return eax;
}
