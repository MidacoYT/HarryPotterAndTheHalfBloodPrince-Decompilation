#pragma optimize("s", on)
#pragma optimize("y", off)
void __fastcall fn_006D6BF1(void *object, int unused, int value)
{
    (void)unused;

    if (value == 0)
        *(int *)((char *)object + 4) &= value;
    else
        *(int *)((char *)object + 4) = value - (int)object;
}
#pragma optimize("y", on)
#pragma optimize("s", off)
