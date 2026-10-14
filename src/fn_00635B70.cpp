struct Own_635B70 { int fn_00635B70(int arg0); };

int Own_635B70::fn_00635B70(int arg0)
{
    int ecx = (int)this;
    int eax, ebx, edx, esi;
    esi = *(int*)((int)&arg0);
    eax = 0;
    edx = (int)((ecx) + 0x14);
    ebx = (int)(ebx);
    L_635B80:;
    if (((unsigned int)(*(int*)(edx))) == ((unsigned int)(esi))) goto L_635B96;
    eax = eax + (1);
    edx = edx + (0x38);
    if (((unsigned int)(eax)) < ((unsigned int)(3))) goto L_635B80;
    L_635B8F:;
    eax = -1;
    return eax;
    L_635B96:;
    edx = (int)((eax) * 8);
    edx = edx - (eax);
    eax = (int)(((ecx) + ((edx) * 8)) + 4);
    if (((unsigned int)(eax)) == ((unsigned int)(0))) goto L_635B8F;
    eax = *(int*)((eax) + 0x1c);
    return eax;
}
