	.text
	.syntax unified
	.thumb
	.global	gcd	
	.type gcd, %function
gcd:
	push {r4-r7}
.WHILE:
	cmp r0,r1
	bgt .MAX		;//if x > y goto max
	movs r2,r0		;//else swap x,y
	movs r0,r1
	movs r1,r2
.MAX:
	subs r0,r1		;//x -= y
	cmp r0,0		;//if x != 0 goto while
	bne .WHILE
	movs r0,r1		;//x = y; return x
	pop {r4-r7}
	bx	lr
