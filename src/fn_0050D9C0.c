void __fastcall fn_0050D9C0(void **slot, void *edx_unused, void **output)
{
    void **destination = *(void ** volatile *)&output;
    void *value = *(void * volatile *)slot;
    (void)edx_unused;
    destination[0] = value;
    destination[1] = 0;
}
