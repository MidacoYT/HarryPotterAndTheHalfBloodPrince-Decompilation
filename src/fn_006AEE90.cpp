struct Layout { unsigned char *base; unsigned countA; unsigned countB; unsigned char *blockC; unsigned char *block10; unsigned char *block14; unsigned countD; unsigned char *block1c; unsigned char *block20; unsigned char *block24; unsigned pad28; unsigned char *block2c; void initialize(); };
void Layout::initialize() {
    unsigned char *p=(unsigned char *)(((unsigned)this+0x3f)&~15u);
    block14=p+(((countA+(countA<<2))<<5));
    base=p;
    blockC=(unsigned char *)(((unsigned)(block14+(countB<<3))+15)&~15u);
    block10=(unsigned char *)(((unsigned)(blockC+(countB<<6))+15)&~15u);
    block24=block10+((countB+(countB<<2))<<4);
    block1c=(unsigned char *)(((unsigned)(block24+(countD<<3))+15)&~15u);
    block20=(unsigned char *)(((unsigned)(block1c+(countD<<5))+15)&~15u);
    block2c=block20+(countD<<6);
}
