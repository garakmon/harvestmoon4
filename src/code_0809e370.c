#define F_SPOKEN_EVER 0x01
#define F_SPOKEN_TODAY 0x20
#define F_SPOKEN_CURRENT_AREA 0x40
#define F_GIVEN_GIFT 0x80

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

//Increases an NPC's affection value
void sub_809E370(struct NPC_RAM_DATA *t, u32 amount) {
    u32 sum = t->Affection + amount;
    u32 affection = sum;
    //Clamps the value if outside 0-255 range
    if ((s32)sum < 0) {
        affection = 0;
    } else if (sum>0xff) {
        affection = 0xff;
    }
    t->Affection = affection;
}

//Decreases an NPC's affection value
void sub_809E38C(struct NPC_RAM_DATA *t, u32 amount){
    sub_809E370(t, -amount);
}

//Sets an NPC's affection value
void sub_809E398(struct NPC_RAM_DATA *t, u32 amount) {
  t->Affection = amount;
}

//Checks if the player has ever talked to this NPC
void sub_809E39C(struct NPC_RAM_DATA *t) {
    u32 r1 = t->Flags2;
    u32 r0 = r1 << 0x1f;
    if (r0 != 0) { //If so, set the F_SPOKEN_TODAY and F_SPOKEN_CURRENT_AREA flags 
        u32 temp = t->Flags1;
        temp |= F_SPOKEN_TODAY;
        temp |= F_SPOKEN_CURRENT_AREA;
        t->Flags1 = temp;
    } else { //Else set the spoken flag
        u32 temp = F_SPOKEN_EVER;
        temp |= r1;
        t->Flags2 = temp;
    }
    r1 = t->Flags1;
    r0 = -0x20;
    r0 &= r1;
    t->Flags1 = r0;
}

//Sets the F_GIVEN_GIFT flag
//The registers get switched up if the second = is not there
void sub_809E3CC(struct NPC_RAM_DATA *t) {
    u32 r1  = t->Flags1 |= F_GIVEN_GIFT;
    r1 &= -0x20;
    t->Flags1 = r1;
}

//Clears F_SPOKEN_CURRENT_AREA
//Called when you go from one area to another and for every NPC (41)
void sub_809E3DC(struct NPC_RAM_DATA *t){
    u32 r2 = t->Flags1;
    u32 r1 = -0x41;
    r1 &= r2;
    t->Flags1 = r1;
}