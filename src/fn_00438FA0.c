int fn_00438FA0(int eax)
{
    int ecx;
eax = *(int*)(eax + 0x9c);
if ((eax) == (0)) goto L_438FBA;
ecx = *(int*)(0x89d928);
if ((ecx) != (*(int*)(eax + 0x50))) goto L_438FBA;
return fn_005B93F0();
L_438FBA:;
return eax;
}
