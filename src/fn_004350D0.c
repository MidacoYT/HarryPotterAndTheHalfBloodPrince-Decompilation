int fn_004350D0(int eax)
{
    int ecx, edx;
ecx = *(int*)(eax);
edx = ecx;
edx = ((unsigned int)(edx)) >> (8);
edx = edx ^ (ecx);
edx = ((unsigned int)(edx)) >> (8);
edx = edx ^ (ecx);
edx = ((unsigned int)(edx)) >> (8);
edx = edx ^ (ecx);
edx = edx & (0xff);
eax = *(int*)((edx) * 4 + 0xd260dc);
if ((eax) == (0)) goto L_435103;
L_4350F4:;
if ((*(int*)(eax + 0x68)) == (ecx)) goto L_435105;
eax = *(int*)(eax + 0x80);
if ((eax) != (0)) goto L_4350F4;
L_435103:;
eax = 0;
L_435105:;
return eax;
}
