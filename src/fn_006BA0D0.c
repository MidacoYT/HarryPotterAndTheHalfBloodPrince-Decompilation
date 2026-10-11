/* Linker/import-library-generated indirect jump thunk (not hand-authored
   game logic): one FF 25 jmp-through-pointer stub per imported symbol,
   reproduced verbatim via naked emit since no C source ever existed for it. */
__declspec(naked) void fn_006BA0D0(void)
{
    __asm {
        _emit 0xFF
        _emit 0x25
        _emit 0xB8
        _emit 0x31
        _emit 0x71
        _emit 0x00
    }
}
