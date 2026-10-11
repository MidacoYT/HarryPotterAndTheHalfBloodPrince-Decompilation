typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

class Candidate {
public:
    Candidate();
};

Candidate::Candidate() {
    *(u32 *)((u8 *)this + 4) = 0;
    *(u32 *)((u8 *)this + 8) = 0;
    *(u32 *)((u8 *)this + 12) = 0;
    *(u32 *)((u8 *)this + 16) = 0;
    *(u32 *)this = 0x008439A8;
    *(u16 *)((u8 *)this + 0x72) = 0xFFFF;
}
