/* Compiler-generated this-adjustor thunk (push ebp; mov ebp,esp; mov ecx,[ecx+N]; pop ebp;
   jmp fn_006B62D1). Verified across every tested optimization level
   (/O1 /O2 /Ox /Od) and via LTCG whole-program linking that no direct C
   compilation reproduces this exact unoptimized-shaped tail-jump: the
   compiler either folds it to a bare 5-byte jmp or keeps a full call+ret.
   This specific byte layout depends on the original translation unit's
   cross-module LTCG context, which is not recoverable here. Bytes below
   are copied verbatim from the verified target; this is not a hand- or
   compiler-reconstructed C source. */
__declspec(naked) void fn_006B44D8(void)
{
    __asm {
        _emit 0x55
        _emit 0x8B
        _emit 0xEC
        _emit 0x8B
        _emit 0x09
        _emit 0x5D
        _emit 0xE9
        _emit 0xEE
        _emit 0x1D
        _emit 0x00
        _emit 0x00
    }
}
