int fn_006E7266(int arg0)
{
    int eax, ecx;
    eax = 0;
    L_6E7268:;
    ecx = *(int*)(eax + 0x852fc8);
    ecx = ecx + (*(int*)((int)&arg0));
    eax = eax + (4);
    *(int*)(eax + 0x89b7f4) = ecx;
    if (((int)(eax)) < ((int)(0x18))) goto L_6E7268;
    return eax;
}
