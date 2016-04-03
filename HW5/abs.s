	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}
	bpl .END		;//if x>=0 goto end
	subs r0,r0,0		;//else x = 0 - x
.END:
	pop {r4-r7}	
	bx	lr
