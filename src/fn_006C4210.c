#pragma optimize("", off)
struct C4210Object {
    unsigned char pad[0x20];
    unsigned int value_20;
    void set_active();
};
void C4210Object::set_active()
{
    this->value_20 = 1;
}
#pragma optimize("", on)
