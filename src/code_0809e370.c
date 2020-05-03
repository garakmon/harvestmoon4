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
    u32 f10:5; // unknown counter
    u32 f11:1; // F_SPOKEN_TODAY
    u32 f12:1; // F_SPOKEN_CURRENT_AREA
    u32 f13:1; // F_GIVEN_GIFT
    u32 f14:1; // F_SPOKEN_EVER
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
//Clears the unknown counter
void sub_809E39C(struct NPC_RAM_DATA *t) {
    if (t->f14 != 0) { //If so, set the F_SPOKEN_TODAY and F_SPOKEN_CURRENT_AREA flags 
        t->f11 = 1;
        t->f12 = 1;
    } else { //Else set the spoken flag
        t->f14 = 1;
    }
    t->f10 = 0;
}

//Sets the F_GIVEN_GIFT flag
//Also clears the unknown counter
void sub_809E3CC(struct NPC_RAM_DATA *t) {
    t->f13 = 1;
    t->f10 = 0;
}

//Clears F_SPOKEN_CURRENT_AREA
//Called when you go from one area to another and for every NPC (41)
void sub_809E3DC(struct NPC_RAM_DATA *t){
    t->f12 = 0;
}

//Checks if the player spoke to an NPC that day
void sub_809E3E8(struct NPC_RAM_DATA *t, u32 param){
    if(t->f11 < 1 && !t->f13){ //If didn't speak or give a gift increase the unknown counter
        if((u32)t->f10 < 0x1f){
            t->f10++;
        }
        if(param < 10){ //If the unknown parameter is less than 10 decrease their affection by 1
            sub_809E38C(t, 1);
        }
    }else{ //Reset the counter if you did 
        t->f10 = 0;
    }
    if(t->f11){ //If you spoke to them increase their affection by 1
        sub_809E370(t, 1);
    }
    //Clear the three flags
    t->f11 = 0;
    t->f12 = 0;
    t->f13 = 0;
}
