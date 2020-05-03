
typedef char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

struct BACHELORETTE_RAM_DATA {
    u32 unknown0; //0-3    0x0-3
    u32 unknown1; //4-7    0x4-7
    u32 unknown2; //8-11   0x8-B
    u32 unknown3; //12-15  0xC-F
    u32 unknown4; //16-19  0x10-13
    u16 Affection; //20-21 0x14-15
    u32 f22:3; //
    u32 f23:3; //
    u32 f24:3; //
    u32 f25:3; //
    u32 f26:3; //
};

//returns a bachelorette's Affection
u16 sub_809E498(struct BACHELORETTE_RAM_DATA *t){
    return t->Affection;
}

//These return the 3 bit unknown values
//sub_809E4B4 is a duplicate of sub_809E4A4
u32 sub_809E49C(struct BACHELORETTE_RAM_DATA *t){
    return t->f22;
}
u32 sub_809E4A4(struct BACHELORETTE_RAM_DATA *t){
    return t->f25;
}
u32 sub_809E4AC(struct BACHELORETTE_RAM_DATA *t){
    return t->f24;
}
u32 sub_809E4B4(struct BACHELORETTE_RAM_DATA *t){
    return t->f25;
}
u32 sub_809E4BC(struct BACHELORETTE_RAM_DATA *t){
    return t->f26;
}

//Increases a bachelorette's affection
void sub_809E4C4(struct BACHELORETTE_RAM_DATA *t,int amount){
    u32 sum = t->Affection + amount;
    u32 affection = sum;
    //Clamps the value if outside 0x0000-0xffff range
    if ((s32)sum < 0) {
        affection = 0;
    }else if (0xffff < sum) {
        affection = 0xffff;
    }
    t->Affection = affection;
}
//Decreases a bachelorette's affection
void sub_809E4E8(struct BACHELORETTE_RAM_DATA *t,int amount){
    sub_809E4C4(t, -amount);
}
//Sets a bachelorette's affection
void sub_809E4F4(struct BACHELORETTE_RAM_DATA *t,int amount){
    t->Affection = amount;
}