void *memcpy(void *destination, const void *source, unsigned int count);
#pragma intrinsic(memcpy)
void __fastcall fn_0055EF40(void *self, void *edx_unused, const void *source)
{
    (void)edx_unused;
    memcpy((unsigned char *)self + 8, source, 0x38);
}
