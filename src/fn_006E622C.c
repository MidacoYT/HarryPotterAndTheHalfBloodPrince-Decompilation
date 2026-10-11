struct S { unsigned char pad[0x0e]; unsigned short value; };
void __cdecl fn_006E622C(struct S *p) {
    if (p->value > 0x2000) p->value = 0x2000;
    else if (p->value < 0x800) p->value = 0x800;
}
