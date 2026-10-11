#pragma optimize("y", off)
typedef struct { volatile unsigned char value; unsigned char pad[3]; } Entry;
unsigned char __cdecl fn_006B3987(int index) { return ((volatile Entry *)0x00851450u)[index * 3].value; }
#pragma optimize("y", on)
