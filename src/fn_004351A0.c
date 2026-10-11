int fn_004351A0(int ecx)
{
    int eax;
eax = ecx;
eax = ((unsigned int)(eax)) >> (8);
eax = eax ^ (ecx);
eax = ((unsigned int)(eax)) >> (8);
eax = eax ^ (ecx);
eax = ((unsigned int)(eax)) >> (8);
eax = eax ^ (ecx);
eax = eax & (0xff);
eax = *(int*)((eax) * 4 + 0xd260dc);
if ((eax) == (0)) goto L_4351D0;
L_4351C1:;
if ((*(int*)(eax + 0x68)) == (ecx)) goto L_4351D2;
eax = *(int*)(eax + 0x80);
if ((eax) != (0)) goto L_4351C1;
L_4351D0:;
eax = 0;
L_4351D2:;
return eax;
}
