struct R { unsigned value, pad1, pad2; }; struct O { unsigned char pad[12]; unsigned value; }; extern "C" __declspec(noinline) R fn_0051BB70(O *obj) { R r; r.value=obj->value; return r; }
