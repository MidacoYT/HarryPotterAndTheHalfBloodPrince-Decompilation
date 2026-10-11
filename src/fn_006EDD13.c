void __fastcall fn_006EDD13(void *self, int unused) {
    unsigned value=*(unsigned *)((char *)self+0x24);
    *(unsigned *)((char *)self+0x30)=0;
    *(unsigned *)((char *)self+0x34)=0;
    *(unsigned *)((char *)self+0x2c)=value;
}
