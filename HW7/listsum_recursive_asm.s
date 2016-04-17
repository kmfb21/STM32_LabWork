	.text
	.syntax unified
	.thumb
	.global	listsum_recursive_asm	
	.type listsum_recursive_asm, %function
listsum_recursive_asm:
	push {r4, lr}		;//save
	cmp r0, 0		;//if !p
	beq .END		;//goto End
	sub sp, 4		;//allocate space size of 4 for p
	str r0, [sp, 4]		;//push p into stack:*(sp+4)=p
	ldr r0, [r0, 4]		;//r0 = p->next
	bl listsum_recursive_asm;//call recursive
	ldr r4, [sp, 4]		;//pop p out: r4=*(sp+4)
	ldr r4, [r4]		;//r4 = p->item
	adds r0, r4		;//r0 += r4
	add sp, 4		;//free space in stack
.END:
	pop {r4, pc}		;//restore
	bx	lr
