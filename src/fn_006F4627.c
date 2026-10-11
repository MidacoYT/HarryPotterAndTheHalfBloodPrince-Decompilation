#pragma optimize("y", off)
#pragma optimize("s", on)
void *__fastcall fn_006F4627(void *self, void *edx_unused, unsigned int index)
{
    index <<= 4;
    return *(unsigned char **)(*(unsigned char **)self + 0x30) + index - 16u;
}
#pragma optimize("y", on)
