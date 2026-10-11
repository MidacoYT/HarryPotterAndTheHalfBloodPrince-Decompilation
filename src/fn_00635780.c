int fn_00635780(int edx)
{
    int eax, ecx;
eax = 0;
ecx = (int)((edx) + 0x10);
L_635785:;
if ((*(int*)(ecx)) == (-1)) goto L_635798;
eax = eax + (1);
ecx = ecx + (0x38);
if (((unsigned int)(eax)) < ((unsigned int)(3))) goto L_635785;
eax = 0;
return eax;
L_635798:;
*(int*)((edx) + 0xa8) = *(int*)((edx) + 0xa8) + (1);
if (((unsigned int)(*(int*)((edx) + 0xa8))) < ((unsigned int)(0x40000000))) goto L_6357B5;
*(int*)((edx) + 0xa8) = 1;
L_6357B5:;
ecx = (int)((eax) * 8);
ecx = ecx - (eax);
eax = (int)((edx) + ((ecx) * 8));
edx = *(int*)((edx) + 0xa8);
*(int*)((eax) + 0x10) = edx;
*(int*)((eax) + 0x1c) = 0xffffffff;
return eax;
}
