void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

unsigned char fn_00691E00(void)
{
    *(volatile unsigned int *)0x00892a20 = 0;
    *(volatile unsigned int *)0x00892a38 = 0x00851150;
    *(volatile unsigned int *)0x00892a24 = 0x008511f0;
    *(volatile unsigned int *)0x00892a28 = 0x008511a0;
    *(volatile unsigned int *)0x00892a2c = 0x00851218;
    *(volatile unsigned int *)0x00892a30 = 0x00851178;
    *(volatile unsigned int *)0x00892a34 = 0x008511c8;
    _ReadWriteBarrier();
    return 1;
}

