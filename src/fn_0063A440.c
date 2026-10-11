int fn_0063A440(int edx)
{
    int eax, ecx;
eax = 0;
ecx = (int)(edx + 0x18);
L_63A445:;
if ((*(int*)(ecx)) == (-1)) goto L_63A458;
eax = eax + (1);
ecx = ecx + (0x70);
if (((int)(eax)) < ((int)(0xa))) goto L_63A445;
eax = 0;
return eax;
L_63A458:;
*(int*)(edx + 0x460) = *(int*)(edx + 0x460) + (1);
if (((unsigned int)(*(int*)(edx + 0x460))) < ((unsigned int)(0x40000000))) goto L_63A475;
*(int*)(edx + 0x460) = 1;
L_63A475:;
ecx = *(int*)(edx + 0x460);
eax = ((int)(eax)) * (0x70);
eax = eax + (edx);
*(int*)(eax + 0x18) = ecx;
return eax;
}
