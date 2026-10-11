void fn_004DA6C0(int ecx, int eax)
{
    int edx;
*(int*)(eax + 4) = ecx;
*(int*)(eax) = 0x82e88c;
edx = 0;
*(int*)(ecx + 0x260) = edx;
ecx = *(int*)(0xfcade0);
*(unsigned char*)(eax + 0xc) = ((unsigned char)edx);
*(int*)(0xfc7f80) = 0x4db2f0;
*(int*)(0xfc7f84) = 0x45df40;
*(int*)(0xfc7e2c) = 0x4db1c0;
*(int*)(0xfc7e30) = 0x4db250;
*(int*)(0xfc7e28) = 0x4db0b0;
*(int*)(ecx + 0x10) = 0x4db300;
*(int*)(eax + 8) = *(int*)(eax + 8) & (0xfffffffe);
*(int*)(0xcef560) = eax;
return;
}
