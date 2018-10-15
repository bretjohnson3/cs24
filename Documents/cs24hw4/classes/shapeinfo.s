	.file	"shapeinfo.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Volume of %s:  %f\tMass of %s:  %f\n\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	print_info
	.type	print_info, @function
print_info:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rsi, %rbx
	movq	%rdi, %rbp
	movq	%rsi, %rdi
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	(%rsi), %rax
	call	*(%rax)
	movq	%rbx, %rdi
	movss	%xmm0, 12(%rsp)
	call	Shape_getMass
	pxor	%xmm2, %xmm2
	movq	%rbp, %rcx
	pxor	%xmm1, %xmm1
	movq	%rbp, %rdx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$2, %eax
	cvtss2sd	12(%rsp), %xmm2
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	cvtss2sd	%xmm0, %xmm1
	movapd	%xmm2, %xmm0
	jmp	__printf_chk
	.cfi_endproc
.LFE38:
	.size	print_info, .-print_info
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC5:
	.string	"cone"
.LC10:
	.string	"box"
.LC13:
	.string	"sphere"
	.section	.text.unlikely
.LCOLDB14:
	.section	.text.startup,"ax",@progbits
.LHOTB14:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorl	%eax, %eax
	call	static_init
	movl	$10, %edi
	call	putchar
	movss	.LC2(%rip), %xmm2
	movss	.LC3(%rip), %xmm1
	movss	.LC4(%rip), %xmm0
	call	new_Cone
	movl	$.LC5, %edi
	movq	%rax, %rbx
	movq	%rax, %rsi
	call	print_info
	movq	%rbx, %rdi
	call	free
	movss	.LC6(%rip), %xmm3
	movss	.LC7(%rip), %xmm2
	movss	.LC8(%rip), %xmm1
	movss	.LC9(%rip), %xmm0
	call	new_Box
	movl	$.LC10, %edi
	movq	%rax, %rbx
	movq	%rax, %rsi
	call	print_info
	movq	%rbx, %rdi
	call	free
	movss	.LC11(%rip), %xmm1
	movss	.LC12(%rip), %xmm0
	call	new_Sphere
	movl	$.LC13, %edi
	movq	%rax, %rbx
	movq	%rax, %rsi
	call	print_info
	movq	%rbx, %rdi
	call	free
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE14:
	.section	.text.startup
.LHOTE14:
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC2:
	.long	1056964608
	.align 4
.LC3:
	.long	1084227584
	.align 4
.LC4:
	.long	1069547520
	.align 4
.LC6:
	.long	1077936128
	.align 4
.LC7:
	.long	1089889894
	.align 4
.LC8:
	.long	1074161254
	.align 4
.LC9:
	.long	1084856730
	.align 4
.LC11:
	.long	1092616192
	.align 4
.LC12:
	.long	1050253722
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
