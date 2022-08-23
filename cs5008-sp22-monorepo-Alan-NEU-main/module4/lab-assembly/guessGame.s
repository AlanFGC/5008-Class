	.file	"guessGame.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"The average number of guesses of the last %d games is: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	$5, -24(%rbp)
	movl	-24(%rbp), %eax
	movslq	%eax, %r8
	subq	$1, %r8
	movq	%r8, -32(%rbp)
	movslq	%eax, %r8
	movq	%r8, %rsi
	movl	$0, %edi
	movslq	%eax, %rsi
	movq	%rsi, %rdx
	movl	$0, %ecx
	cltq
	salq	$2, %rax
	leaq	3(%rax), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %edi
	movl	$0, %edx
	divq	%rdi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -40(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L2
.L3:
	movl	$0, %eax
	call	playGame
	movq	-40(%rbp), %rdx
	movl	-20(%rbp), %ecx
	movslq	%ecx, %rcx
	movl	%eax, (%rdx,%rcx,4)
	addl	$1, -20(%rbp)
.L2:
	movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L3
	movq	-40(%rbp), %rax
	movl	-24(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	printScores
	movq	-40(%rbp), %rax
	movl	-24(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	getAverage
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %edx
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	movq	%rbx, %rsp
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.string	"================================================="
	.align 8
.LC2:
	.string	"|Here are the results of your guessing abilities|"
.LC3:
	.string	"Game %d took you %d guesses\n"
	.text
	.globl	printScores
	.type	printScores, @function
printScores:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$.LC1, %edi
	call	puts
	movl	$.LC2, %edi
	call	puts
	movl	$.LC1, %edi
	call	puts
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	-4(%rbp), %edx
	leal	1(%rdx), %ecx
	movl	%eax, %edx
	movl	%ecx, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L6:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L7
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	printScores, .-printScores
	.globl	getAverage
	.type	getAverage, @function
getAverage:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	.LC4(%rip), %eax
	movl	%eax, -8(%rbp)
	cvtsi2ss	-44(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L10
.L11:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cvtsi2ss	%eax, %xmm0
	movss	-8(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	addl	$1, -12(%rbp)
.L10:
	movl	-12(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L11
	movss	-8(%rbp), %xmm0
	divss	-16(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-20(%rbp), %xmm0
	cvttss2si	%xmm0, %eax
	movl	%eax, -24(%rbp)
	cvtsi2ss	-24(%rbp), %xmm0
	movss	-20(%rbp), %xmm1
	subss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	movss	%xmm0, -28(%rbp)
	movss	-28(%rbp), %xmm0
	ucomiss	.LC5(%rip), %xmm0
	jbe	.L17
	movss	-20(%rbp), %xmm1
	movss	.LC6(%rip), %xmm0
	addss	%xmm1, %xmm0
	cvttss2si	%xmm0, %eax
	movl	%eax, -4(%rbp)
	jmp	.L14
.L17:
	movss	-20(%rbp), %xmm0
	cvttss2si	%xmm0, %eax
	movl	%eax, -4(%rbp)
.L14:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	getAverage, .-getAverage
	.section	.rodata
	.align 8
.LC7:
	.string	"============================================"
	.align 8
.LC8:
	.string	"CPU says: Pick a random number from 1 - 20"
.LC9:
	.string	"Make a guess:\t"
.LC10:
	.string	"%d"
.LC11:
	.string	"Too Low"
.LC12:
	.string	"Too High"
	.align 8
.LC13:
	.string	"Correct! - Number of guesses:%d\n"
	.text
	.globl	playGame
	.type	playGame, @function
playGame:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$20, %esi
	movl	$1, %edi
	call	randInRange
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	movl	$.LC7, %edi
	call	puts
	movl	$.LC8, %edi
	call	puts
	movl	$.LC7, %edi
	call	puts
	jmp	.L19
.L22:
	movl	$.LC9, %edi
	movl	$0, %eax
	call	printf
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC10, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	addl	$1, -4(%rbp)
	movl	-12(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.L20
	movl	$.LC11, %edi
	call	puts
	jmp	.L19
.L20:
	movl	-12(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	.L21
	movl	$.LC12, %edi
	call	puts
	jmp	.L19
.L21:
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC13, %edi
	movl	$0, %eax
	call	printf
.L19:
	movl	-12(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jne	.L22
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	playGame, .-playGame
	.globl	randInRange
	.type	randInRange, @function
randInRange:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	-20(%rbp), %eax
	movl	-24(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	movl	$0, %edi
	call	time
	movl	%eax, %edi
	call	srand
	call	rand
	cltd
	idivl	-4(%rbp)
	movl	%edx, %eax
	cvtsi2ss	%eax, %xmm0
	movss	%xmm0, -8(%rbp)
	cvtsi2ss	-20(%rbp), %xmm0
	movss	-8(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-8(%rbp), %xmm0
	cvttss2si	%xmm0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	randInRange, .-randInRange
	.section	.rodata
	.align 4
.LC4:
	.long	0
	.align 4
.LC5:
	.long	1056964608
	.align 3
.LC6:
	.long	1065353216
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
