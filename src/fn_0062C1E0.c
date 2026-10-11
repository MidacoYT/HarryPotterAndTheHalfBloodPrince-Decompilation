int fn_0062C1E0(int eax, int ecx)
{
eax = *(int*)(eax + 0x34);
if ((eax) == (0)) goto L_62C206;
eax = *(int*)(eax);
if ((eax) == (0)) goto L_62C206;
ecx = (int)(ecx);
L_62C1F0:;
if ((*(int*)(eax + 4)) == (ecx)) goto L_62C201;
eax = *(int*)(eax);
if ((eax) != (0)) goto L_62C1F0;
eax = 0x80282c;
return eax;
L_62C201:;
eax = eax + (8);
if ((eax) != (0)) goto L_62C20B;
L_62C206:;
eax = 0x80282c;
L_62C20B:;
return eax;
}
