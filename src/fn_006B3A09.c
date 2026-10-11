#pragma optimize("", off)
struct ByteSlot { unsigned char first; unsigned char rest[7]; };
unsigned char __cdecl fn_006B3A09(int param_1) { return ((struct ByteSlot *)0x008514AC)[param_1].first; }
#pragma optimize("", on)
