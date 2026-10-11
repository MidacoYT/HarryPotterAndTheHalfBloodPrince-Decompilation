
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;

int32_t fcn_0048ab80(int eax)
{
    int ecx;

    ecx = *(int*)(0xd27a14);
    *(int*)(eax) = ecx;
    return eax;
}
