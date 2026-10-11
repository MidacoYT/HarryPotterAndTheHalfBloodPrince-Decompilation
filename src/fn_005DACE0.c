void __debugbreak(void);
#pragma intrinsic(__debugbreak)

__declspec(naked) void fn_005DACE0(void)
{
    __debugbreak();
}
