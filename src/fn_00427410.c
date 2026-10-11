int fn_00427410(void)
{
    int eax, ecx;
    eax = 0;
    ecx = 0xcf6358;
    L_427417:;
    if ((*(int*)(ecx)) == (0)) goto L_427430;
    ecx = ecx + (0x660);
    eax = eax + (1);
    if (((int)(ecx)) < ((int)(0xcf7cd8))) goto L_427417;
    eax = 0;
    return eax;
    L_427430:;
    eax = ((int)(eax)) * (0x660);
    eax = eax + (0xcf6350);
    return eax;
}
