	.text
	.syntax unified
	.thumb
	.global	fib	
	.type fib, %function
fib:
	push {r4-r7}
	movs r2,r0		;//r2 = x
	cmp r0,2
	blt .END		;//if x < 2 goto end
	movs r1,0		;//else r1=0,r2=1
	movs r2,1
.LOOP:
	adds r1,r2		;//r1 += r2
	movs r3,r1		;//swap r1,r2
	movs r1,r2
	movs r2,r3
	subs r0,1		;//x--
	cmp r0,1
	bne .LOOP		;//if x != 1 goto loop
.END:
	movs r0,r2		;//return x = r2
	pop {r4-r7}
	bx	lr			
