int fn_0055CF80(int eax)
{
    int ecx, edx;
ecx = *(int*)((eax) + 0x32c);
if ((ecx) == (0)) goto L_55CFAA;
edx = *(int*)((ecx) + 0x50);
eax = *(int*)(((edx) * 4) + 0xd254c0);
edx = (unsigned char)(*(unsigned char*)((eax) + 0x7a));
if ((edx) == (0xff)) goto L_55CFAA;
eax = *(int*)((eax) + 0x10);
eax = *(int*)((eax) + ((edx) * 8));
eax = eax + (ecx);
if ((eax) != (0)) goto L_55CFAC;
L_55CFAA:;
eax = 0;
L_55CFAC:;
return eax;
}
