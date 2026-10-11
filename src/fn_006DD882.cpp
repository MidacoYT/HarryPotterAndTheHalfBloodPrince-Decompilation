class Holder { public: unsigned int get(int index); };
unsigned int __thiscall Holder::get(int index) { return *((unsigned char *)this + index + 0x234); }
