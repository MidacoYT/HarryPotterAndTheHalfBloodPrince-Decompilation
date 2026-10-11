int fn_00477E40(int edx)
{
    int eax, ecx;
eax = 0;
ecx = (int)((edx) + 0x1dc);
L_477E48:;
if ((*(int*)((ecx) - 0x14)) == (0)) goto L_477E53;
if ((*(unsigned char*)(ecx)) == (0)) goto L_477E79;
L_477E53:;
eax = eax + (1);
ecx = ecx + (0x20);
if (((int)(eax)) < ((int)(5))) goto L_477E48;
eax = 0;
ecx = (int)((edx) + 0x1c8);
L_477E66:;
if ((*(int*)(ecx)) != (0)) goto L_477E79;
eax = eax + (1);
ecx = ecx + (0x20);
if (((int)(eax)) < ((int)(5))) goto L_477E66;
eax = 0;
return eax;
L_477E79:;
eax = ((unsigned int)(eax)) << (5);
eax = *(int*)(((eax) + (edx)) + 0x1c8);
return eax;
}
