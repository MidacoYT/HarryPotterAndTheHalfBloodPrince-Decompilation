typedef struct RefObject { void *vtable; int refs; } RefObject;
typedef void (__fastcall *ReleaseFn)(RefObject *);
void __stdcall fn_006172B0(void *owner, void *unused)
{
    RefObject *object = *(RefObject **)((char *)owner + 0x20);
    (void)unused;
    if (object != 0) {
        object->refs--;
        if (object->refs == 0) ((ReleaseFn)((void **)object->vtable)[2])(object);
        *(RefObject **)((char *)owner + 0x20) = 0;
    }
}
