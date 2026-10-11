int fn_005DAFA0(int esi)
{
    int eax, ebx, ecx, edx;
edx = *(int*)(esi);
eax = edx;
if ((edx) == (esi)) goto L_5DAFC5;
ecx = *(int*)(0x892990);
L_5DAFB0:;
eax = *(int*)(eax);
ebx = *(int*)(ecx + 8);
*(int*)(ecx + 0xc) = *(int*)(ecx + 0xc) + (-1);
*(int*)(edx) = ebx;
*(int*)(ecx + 8) = edx;
edx = eax;
if ((eax) != (esi)) goto L_5DAFB0;
L_5DAFC5:;
return eax;
}
