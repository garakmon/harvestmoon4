    .INCLUDE "asm/macro.inc"
    .SYNTAX UNIFIED

	thumb_func_start sub_809E458
sub_809E458: @ 0x0809E458
	push {r4, lr}
	adds r4, r0, #0
	bl sub_809E2D4
	movs r0, #0
	strh r0, [r4, #0x14]
	ldrb r1, [r4, #0x16]
	subs r0, #8
	ands r0, r1
	movs r1, #0x39
	rsbs r1, r1, #0
	ands r0, r1
	strb r0, [r4, #0x16]
	ldrh r1, [r4, #0x16]
	ldr r0, _0809E494 @ =0xFFFFFE3F
	ands r0, r1
	strh r0, [r4, #0x16]
	ldrb r1, [r4, #0x17]
	movs r0, #0xf
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #0x71
	rsbs r1, r1, #0
	ands r0, r1
	strb r0, [r4, #0x17]
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_0809E494: .4byte 0xFFFFFE3F
