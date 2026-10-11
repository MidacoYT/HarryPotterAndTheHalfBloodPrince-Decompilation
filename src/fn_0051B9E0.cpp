struct R { unsigned value, pad1, pad2; }; struct O { unsigned char pad[0x68]; unsigned value; }; extern "C" __declspec(noinline) R fn_0051B9E0(O *obj) { R r; r.value = obj->value; return r; }
