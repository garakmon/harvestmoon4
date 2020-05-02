    .INCLUDE "asm/macro.inc"
    .SYNTAX UNIFIED

	thumb_func_start sub_809E368
sub_809E368: @ 0x0809E368
	ldm r1!, {r2, r3}
	stm r0!, {r2, r3}
	bx lr
	.align 2, 0
