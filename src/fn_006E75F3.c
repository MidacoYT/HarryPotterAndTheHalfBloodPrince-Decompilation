extern void fn_006E5824(int);

int fn_006E75F3(int arg0)
{
    int eax, ebx, ecx, edi, esi, local_Ch;
    esi = *(int*)((int)&arg0);
    ebx = 0;
    if (((unsigned int)(*(unsigned char*)(esi))) <= ((unsigned int)(((unsigned char)ebx)))) goto L_6E7618;
    edi = (int)(esi + 4);
    L_6E7603:;
    eax = (signed short)(*(unsigned short*)(edi));
    fn_006E5824(eax);
    eax = (unsigned char)(*(unsigned char*)(esi));
    ebx = ebx + 1;
    edi = edi + 1;
    edi = edi + 1;
    ecx = local_Ch;
    if (((int)(ebx)) < ((int)(eax))) goto L_6E7603;
    L_6E7618:;
    eax = 0;
    return eax;
}
