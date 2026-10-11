int fn_005A6DE0(int esi)
{
    int eax, ecx, edx;
eax = 0;
ecx = (int)((esi) + 0x290);
L_5A6DE8:;
edx = *(int*)(ecx);
if ((edx) == (0)) goto L_5A6E02;
if ((*(int*)((edx) + 0x38)) == (0)) goto L_5A6E02;
eax = eax + (1);
ecx = ecx + (4);
if (((int)(eax)) < ((int)(2))) goto L_5A6DE8;
eax = 0;
return eax;
L_5A6E02:;
eax = (int)(((esi) + ((eax) * 4)) + 0x290);
*(int*)(eax) = 0;
return eax;
}
