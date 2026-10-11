extern int __stdcall fn_53CC00(void *context, void *object);
extern void __stdcall fn_53CF50(void *context, void *result);

unsigned char fn_48AE70(void * volatile object)
{
    register void *object_copy = object;
    void *context = *(void * volatile *)0x00FCADE8;
    void *result = (void *)fn_53CC00(context, object_copy);
    if (result != 0) {
        fn_53CF50(context, result);
        return 1;
    }
    return 0;
}
