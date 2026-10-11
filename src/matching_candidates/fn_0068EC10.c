float __cdecl fn_0068EC10(float value) {
    float old = *(volatile float *)0x008510b4;
    *(volatile float *)0x008510b4 = value;
    return old;
}
