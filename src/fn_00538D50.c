unsigned int *__fastcall fn_00538D50(void *object)
{
    unsigned int *flags = (unsigned int *)((unsigned char *)object + 0xD8);
    if ((*flags & 0x10000000u) != 0)
        return (unsigned int *)*flags;

    *flags &= 0xEFFFFFFFu;
    unsigned int *state = *(unsigned int **)((unsigned char *)object + 0x14);
    state[0x18C / 4] &= 0xFFBFFFFFu;
    return state;
}
