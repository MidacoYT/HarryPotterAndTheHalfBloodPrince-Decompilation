struct S { char pad[0x4f8]; float other; float val; }; float fn_006080B0(struct S *p) { return p->val >= *(float *)0x831C2C ? p->val : p->other; }
