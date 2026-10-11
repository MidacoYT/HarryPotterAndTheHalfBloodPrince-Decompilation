int fn_004926B0(int esi, int eax)
{
    int ecx, edx;
ecx = 0;
edx = (int)((esi) + 4);
L_4926B5:;
if ((*(int*)(edx)) == (eax)) goto L_4926C5;
ecx = ecx + (1);
edx = edx + (4);
if (((int)(ecx)) < ((int)(0xe))) goto L_4926B5;
L_4926C4:;
return eax;
L_4926C5:;
*(int*)(((esi) + ((ecx) * 4)) + 4) = 0;
if ((*(unsigned char*)((eax) + 0x15)) == (0)) goto L_4926C4;
if ((*(unsigned char*)((eax) + 0x14)) != (1)) goto L_4926C4;
*(int*)((eax) + 0x18) = 0xffffffff;
*(unsigned char*)((eax) + 0x15) = 0;
return fn_004554F0();
}
