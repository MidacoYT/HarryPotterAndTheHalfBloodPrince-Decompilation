
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;

extern void fn_006F1003(void);

void fn_006EA354(void)
{
    fn_006F1003();
    *(int*)(0x89b5e0) = 0x6f0fd4;
    *(int*)(0x89b640) = 0x2c;
    *(int*)(0x89b5e4) = 0x6f0f17;
    *(int*)(0x89b644) = 0x30;
    *(int*)(0x89b5e8) = 0x6f0e5d;
    *(int*)(0x89b648) = 0x34;
}
