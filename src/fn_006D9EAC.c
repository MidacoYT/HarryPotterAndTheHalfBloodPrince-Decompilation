
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;

extern int fn_006B175B(int, int, int);
extern void fn_006B17E5(int, int);
extern int fn_006B1815(int, int);

int32_t fn_006D9EAC(int arg_8h, int arg_ch)
{
    int eax, ebx, esi, edi;

    eax = arg_ch;
    esi = arg_8h;
    eax = fn_006B175B(*(int*)(eax), 1, esi);
    edi = eax;
    if (edi != 0) {
        esi--;
        eax = fn_006B1815(edi, esi);
        ebx = eax;
        fn_006B17E5(edi, esi);
        eax = ebx;
    } else {
        eax = 0;
    }
    return eax;
}
