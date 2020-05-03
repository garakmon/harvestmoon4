
typedef char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

struct NPC_RAM_DATA {
    u32 unknown0; //0-3
    u32 unknown1; //4-7
    u8 Affection; //8
    u32 f10:5; //
    u32 f11:1; // F_SPOKEN_TODAY
    u32 f12:1; // F_SPOKEN_CURRENT_AREA
    u32 f13:1; // F_GIVEN_GIFT
    u32 f14:1; // F_SPOKEN_EVER
};
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

void sub_809E4F8(struct BACHELORETTE_RAM_DATA *t){
    if((u32)t->f22 < 6){
        t->f22++;
        t->f23 = 0;
    }
}
void sub_809E520(struct BACHELORETTE_RAM_DATA *t){
    if((u32)t->f24 < 5){
        t->f24++;
        t->f25 = 0;
    }
}
void sub_809E550(struct BACHELORETTE_RAM_DATA *t){
    if((u32)t->f26 < 5){
        t->f26++;
    }
}

//uknown functions
extern u32 sub_80D11E4();
extern u32 sub_80D0ED0(u32 param_1, u32 param_2);
// TODO: refactor these into a header
extern u8 sub_809E350(struct NPC_RAM_DATA *t);
extern void sub_809E3E8(struct NPC_RAM_DATA *t, u32 param);
extern u32 sub_809E340(struct NPC_RAM_DATA *t);

//Checks if you talked to a bachelorette
void sub_809E574(struct BACHELORETTE_RAM_DATA *t, u8 param_2, u32 param_3){
    if(sub_809E350((struct NPC_RAM_DATA *)t)){ //F_SPOKEN_TODAY
        sub_809E4C4(t, 200); //Increase affection if so
    }
    sub_809E3E8((struct NPC_RAM_DATA *)t, param_3); //Calls the NPC version of the method
    if(sub_809E340((struct NPC_RAM_DATA *)t) && param_3 < 10){ //If the unknown counter!=0 and param_3 < 10
        sub_809E4E8(t, 200); //Decrease the affection
    }
    if(param_2 != 0){
        if((u32)t->f22 > 5){ //If one of the unknown 3bit values > 5
            if(4 < sub_809E340((struct NPC_RAM_DATA *)t)){ //And the counter is > 4
                if((s32)sub_80D0ED0(sub_80D11E4(), 100) < 10){ //No idea what these functions do, they seem to be handwritten assembly
                    sub_809E4E8(t, 1000); //Decrease affection
                }
            }
        }else{ //Decrease affection
            sub_809E4E8(t, 100);
        }
    }
    if((u32)t->f23 < 7){
        t->f23++;
    }
    if((u32)t->f25 < 7){
        t->f25++;
    }
}
