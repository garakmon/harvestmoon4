typedef char u8;
typedef unsigned int u32;
typedef int s32;

struct NPC_RAM_DATA {
    u32 unknown0; //0-3
    u32 unknown1; //4-7
    u8 Affection; //8
    u32 f10:5; // unknown counter
    u32 f11:1; // F_SPOKEN_TODAY
    u32 f12:1; // F_SPOKEN_CURRENT_AREA
    u32 f13:1; // F_GIVEN_GIFT
    u32 f14:1; // F_SPOKEN_EVER
};

//returns an NPC's Affection
u8 sub_809E33C(struct NPC_RAM_DATA *t) {
    return t->Affection;
}

//Returns an unknown counter
u8 sub_809E340(struct NPC_RAM_DATA *t) {
    return t->f10;
}
//Returns F_GIVEN_GIFT
u8 sub_809E348(struct NPC_RAM_DATA *t) {
    return t->f13;
}
//Returns F_SPOKEN_TODAY
u8 sub_809E350(struct NPC_RAM_DATA *t) {
    return t->f11;
}
//Returns F_SPOKEN_CURRENT_AREA
u8 sub_809E358(struct NPC_RAM_DATA *t) {
    return t->f12;
}
//Returns F_SPOKEN_EVER
u8 sub_809E360(struct NPC_RAM_DATA *t) {
    return t->f14;
}
