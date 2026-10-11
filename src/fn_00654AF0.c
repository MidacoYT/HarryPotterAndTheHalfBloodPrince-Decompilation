typedef struct { unsigned char pad0[8]; signed char count; unsigned char pad1[3]; void **values; } Inner;
typedef struct { unsigned char pad[12]; Inner *entry; } Outer;
__declspec(noinline) void *fn_00654AF0(Outer *object, int index)
{
    Inner *entry = object->entry;
    if (!entry || index < 0 || index >= entry->count)
        return 0;
    return entry->values[index];
}
