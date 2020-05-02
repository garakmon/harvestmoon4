typedef char u8;
typedef unsigned int u32;
typedef int s32;

struct NPC_RAM_DATA {
    u32 unknown0; //0-3
    u32 unknown1; //4-7
    u8 Affection; //8
    u8 Flags1; //9
    u8 Flags2; //10
};

//returns an NPC's Affection
u8 sub_809E33C(struct NPC_RAM_DATA *t) {
    return t->Affection;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//All the following functions return the specified flag in bit 0 with all other bits cleared//
//////////////////////////////////////////////////////////////////////////////////////////////

//Returns an unknown flag 
u8 sub_809E340(struct NPC_RAM_DATA *t) {
    return ((u32)t->Flags1 << 0x1b) >> 0x1b;
}
//Returns F_GIVEN_GIFT
u8 sub_809E348(struct NPC_RAM_DATA *t) {
    return t->Flags1 >> 7;
}
//Returns F_SPOKEN_TODAY
u8 sub_809E350(struct NPC_RAM_DATA *t) {
    return ((u32)t->Flags1 << 0x1a) >> 0x1f;
}
//Returns F_SPOKEN_CURRENT_AREA
u8 sub_809E358(struct NPC_RAM_DATA *t) {
    return ((u32)t->Flags1 << 0x19) >> 0x1f;
}
//Returns F_SPOKEN_EVER
u8 sub_809E360(struct NPC_RAM_DATA *t) {
    return ((u32)t->Flags2 << 0x1f) >> 0x1f;
}
