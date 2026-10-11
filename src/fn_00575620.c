int fn_00575620(int eax, int edi)
{
    int ecx, edx, esi;
esi = *(int*)((eax) + 8);
if ((esi) == (0)) goto L_575642;
edx = *(int*)((esi) + 0x10);
eax = 0;
if (((unsigned int)(edx)) <= ((unsigned int)(0))) goto L_575642;
ecx = (int)((esi) + 0x18);
L_575634:;
if ((*(int*)(ecx)) == (edi)) goto L_575646;
eax = eax + (1);
ecx = ecx + (0xc);
if (((unsigned int)(eax)) < ((unsigned int)(edx))) goto L_575634;
L_575642:;
eax = 0;
return eax;
L_575646:;
ecx = (int)((eax) + ((eax) * 2));
eax = *(int*)(((esi) + ((ecx) * 4)) + 0x1c);
return eax;
}
