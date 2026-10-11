struct R { unsigned value, pad1, pad2; }; struct O { unsigned char pad[28]; unsigned value; }; extern "C" __declspec(noinline) R fn_004D5520(O *obj) { R r; r.value=obj->value; return r; }
