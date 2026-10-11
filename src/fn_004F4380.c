int fn_004F4380(int edx)
{
    int eax, ecx;
eax = 0;
ecx = 0xd3a5d8;
L_4F4387:;
if (((int)(eax)) >= ((int)(8))) goto L_4F43A3;
if (((*(unsigned char*)((ecx) + 0x50) & 1)) == (0)) goto L_4F4398;
*(int*)((edx) + ((eax) * 4)) = ecx;
eax = eax + (1);
L_4F4398:;
ecx = ecx + (0x58);
if (((int)(ecx)) < ((int)(0xd3a898))) goto L_4F4387;
L_4F43A3:;
return eax;
}
