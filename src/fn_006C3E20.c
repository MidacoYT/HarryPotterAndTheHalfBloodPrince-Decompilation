#pragma optimize("", off)
typedef unsigned int u32;
struct C3E20Object {
    unsigned char pad[0x10c];
    u32 value_10c;
    u32 value_110;
    void set(u32 value_10c, u32 value_110);
};
void C3E20Object::set(u32 value_10c, u32 value_110)
{
    this->value_10c = value_10c;
    this->value_110 = value_110;
}
#pragma optimize("", on)
