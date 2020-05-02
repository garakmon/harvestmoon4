    .INCLUDE "asm/macro.inc"
    .SYNTAX UNIFIED
    
    @ This function checks if the player talked to an NPC that day
    @ if so increase their affection by 1, else decrease it by 1

	thumb_func_start sub_809E3E8
sub_809E3E8: @ 0x0809E3E8
	push {r4, lr}
	adds r4, r0, #0
	adds r3, r1, #0
	ldrb r2, [r4, #9]
	lsls r0, r2, #0x1a
	cmp r0, #0
	blt _0809E422
	lsrs r0, r2, #7
	cmp r0, #0
	bne _0809E422
	lsls r0, r2, #0x1b
	lsrs r0, r0, #0x1b
	cmp r0, #0x1e
	bhi _0809E414
	adds r1, r0, #1
	movs r0, #0x1f
	ands r1, r0
	movs r0, #0x20
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4, #9]
_0809E414:
	cmp r3, #9
	bhi _0809E42C
	adds r0, r4, #0
	movs r1, #1
	bl sub_809E38C
	b _0809E42C
_0809E422:
	ldrb r1, [r4, #9]
	movs r0, #0x20
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #9]
_0809E42C:
	ldrb r0, [r4, #9]
	lsls r0, r0, #0x1a
	cmp r0, #0
	bge _0809E43C
	adds r0, r4, #0
	movs r1, #1
	bl sub_809E370
_0809E43C:
	ldrb r1, [r4, #9]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #0x41
	rsbs r1, r1, #0
	ands r0, r1
	movs r1, #0x7f
	ands r0, r1
	strb r0, [r4, #9]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0