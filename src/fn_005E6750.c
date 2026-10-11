int fn_005E6750(int eax, int ecx)
{
    eax = *(int*)(eax + 4);
    if ((eax) == (0)) goto L_5E6769;
    if ((*(unsigned char*)(eax + 0x45)) != (1)) goto L_5E6769;
    eax = *(int*)(0xcef73c);
    if ((eax) == (0)) goto L_5E6769;
    *(int*)(eax + 8) = ecx;
    L_5E6769:;
    return eax;
}
