#pragma optimize("", off)
struct PointerPair { void *first; void *second; };
void * __cdecl fn_006B3A41(int param_1) { return ((struct PointerPair *)0x008514A8)[param_1].first; }
#pragma optimize("", on)
