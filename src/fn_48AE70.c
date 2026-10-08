typedef unsigned char u8;

/* Documented role: DeactivateScreenNoFocus. */
extern void * __stdcall fn_53CC00(void *manager, void *key);
extern void __stdcall fn_53CF50(void *manager, void *entry);

u8 __cdecl fn_48AE70(void *key)
{
    void *manager = *(void **)0x00FCADE8;
    void *entry = fn_53CC00(manager, key);
    if (entry != 0) {
        fn_53CF50(manager, entry);
        return 1;
    }
    return 0;
}
