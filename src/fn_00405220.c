void fn_00405220(int ecx, int eax)
{
    int edx;
edx = *(int*)(ecx + 0x190);
*(int*)(eax) = edx;
edx = *(int*)(ecx + 0x194);
*(int*)(eax + 4) = edx;
edx = *(int*)(ecx + 0x198);
ecx = *(int*)(ecx + 0x19c);
*(int*)(eax + 8) = edx;
*(int*)(eax + 0xc) = ecx;
return;
}
