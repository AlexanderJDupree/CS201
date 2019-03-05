	.file	"bigint.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"src/bigint.c"
.LC1:
	.string	"b->buckets"
	.section	.text.unlikely,"ax",@progbits
	.type	bigint_new.part.0, @function
bigint_new.part.0:
.LFB62:
	.cfi_startproc
	leaq	__PRETTY_FUNCTION__.3499(%rip), %rcx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$16, %edx
	call	__assert_fail@PLT
	.cfi_endproc
.LFE62:
	.size	bigint_new.part.0, .-bigint_new.part.0
	.section	.rodata.str1.1
.LC2:
	.string	"b"
	.text
	.p2align 4,,15
	.globl	bigint_new
	.type	bigint_new, @function
bigint_new:
.LFB54:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	%edi, %ebp
	movl	$16, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	malloc@PLT
	testq	%rax, %rax
	je	.L8
	movslq	%ebp, %rdi
	movq	%rax, %rbx
	salq	$3, %rdi
	call	malloc@PLT
	testq	%rax, %rax
	movq	%rax, 8(%rbx)
	je	.L9
	movl	%ebp, (%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	leaq	__PRETTY_FUNCTION__.3499(%rip), %rcx
	leaq	.LC0(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	movl	$14, %edx
	call	__assert_fail@PLT
.L9:
	call	bigint_new.part.0
	.cfi_endproc
.LFE54:
	.size	bigint_new, .-bigint_new
	.p2align 4,,15
	.globl	bigint_free
	.type	bigint_free, @function
bigint_free:
.LFB55:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	8(%rdi), %rdi
	call	free@PLT
	movq	%rbx, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.cfi_endproc
.LFE55:
	.size	bigint_free, .-bigint_free
	.section	.rodata.str1.1
.LC3:
	.string	"j < ns"
.LC4:
	.string	"d >= 'a' && d <= 'f'"
	.text
	.p2align 4,,15
	.globl	bigint_read
	.type	bigint_read, @function
bigint_read:
.LFB57:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	movq	%rdi, 16(%rsp)
	call	strlen@PLT
	testl	%eax, %eax
	movq	%rax, 56(%rsp)
	movl	%eax, 28(%rsp)
	je	.L27
	leal	30(%rax), %ebx
	addl	$15, %eax
	movl	$16, %edi
	cmovns	%eax, %ebx
	sarl	$4, %ebx
	call	malloc@PLT
	testq	%rax, %rax
	movq	%rax, %r15
	je	.L33
	movslq	%ebx, %rdi
	salq	$3, %rdi
	call	malloc@PLT
	testq	%rax, %rax
	movq	%rax, 32(%rsp)
	movq	%rax, 8(%r15)
	je	.L34
	movl	%ebx, %eax
	movl	%ebx, (%r15)
	subl	$1, %eax
	movl	%eax, 48(%rsp)
	js	.L12
	movslq	%eax, %rsi
	movl	%eax, %eax
	xorl	%ebp, %ebp
	leaq	-1(%rsi), %rdx
	movq	%rsi, 8(%rsp)
	movq	%r15, 72(%rsp)
	subq	%rax, %rdx
	movq	16(%rsp), %rax
	movq	%rdx, 64(%rsp)
	addq	$1, %rax
	movq	%rax, 40(%rsp)
	movl	56(%rsp), %eax
	subl	$1, %eax
	movl	%eax, 52(%rsp)
.L26:
	movl	8(%rsp), %ecx
	cmpl	%ecx, 48(%rsp)
	je	.L35
	movl	$16, %r12d
.L16:
	leal	0(%rbp,%r12), %eax
	cmpl	%eax, %ebp
	movl	%eax, 24(%rsp)
	jge	.L29
	cmpl	28(%rsp), %ebp
	jge	.L19
	call	__ctype_b_loc@PLT
	movq	(%rax), %r13
	movq	16(%rsp), %rax
	movslq	%ebp, %rbx
	xorl	%r14d, %r14d
	leaq	(%rax,%rbx), %r15
	addq	40(%rsp), %rbx
	movl	52(%rsp), %eax
	subl	%ebp, %eax
	notl	%ebp
	addq	%rax, %rbx
	movl	24(%rsp), %eax
	addl	%eax, %ebp
	addq	%r15, %rbp
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L22:
	call	__ctype_tolower_loc@PLT
	movq	(%rax), %rax
	movl	(%rax,%r12,4), %eax
	leal	-97(%rax), %edx
	cmpb	$5, %dl
	ja	.L36
	movsbl	%al, %eax
	salq	$4, %r14
	subl	$87, %eax
	cltq
	orq	%rax, %r14
	cmpq	%r15, %rbp
	je	.L37
.L25:
	addq	$1, %r15
	cmpq	%r15, %rbx
	je	.L19
.L20:
	movsbq	(%r15), %r12
	testb	$16, 1(%r13,%r12,2)
	movq	%r12, %rax
	je	.L38
	leal	-48(%r12), %edx
	cmpb	$9, %dl
	ja	.L22
	subl	$48, %eax
	salq	$4, %r14
	cltq
	orq	%rax, %r14
	cmpq	%r15, %rbp
	jne	.L25
.L37:
	movl	24(%rsp), %ebp
.L17:
	movq	8(%rsp), %rax
	movq	32(%rsp), %rsi
	movq	%r14, (%rsi,%rax,8)
	subq	$1, %rax
	cmpq	64(%rsp), %rax
	movq	%rax, 8(%rsp)
	jne	.L26
	movq	72(%rsp), %r15
.L12:
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r15, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L38:
	.cfi_restore_state
	movq	72(%rsp), %r15
	movq	32(%rsp), %rdi
	call	free@PLT
	movq	%r15, %rdi
	xorl	%r15d, %r15d
	call	free@PLT
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L27:
	xorl	%r15d, %r15d
	jmp	.L12
.L29:
	xorl	%r14d, %r14d
	movl	%eax, %ebp
	jmp	.L17
.L35:
	movl	56(%rsp), %r12d
	movl	%ecx, %eax
	sall	$4, %eax
	subl	%eax, %r12d
	jmp	.L16
.L19:
	leaq	__PRETTY_FUNCTION__.3522(%rip), %rcx
	leaq	.LC0(%rip), %rsi
	leaq	.LC3(%rip), %rdi
	movl	$73, %edx
	call	__assert_fail@PLT
.L36:
	leaq	__PRETTY_FUNCTION__.3509(%rip), %rcx
	leaq	.LC0(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	movl	$32, %edx
	call	__assert_fail@PLT
.L34:
	call	bigint_new.part.0
.L33:
	leaq	__PRETTY_FUNCTION__.3499(%rip), %rcx
	leaq	.LC0(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	movl	$14, %edx
	call	__assert_fail@PLT
	.cfi_endproc
.LFE57:
	.size	bigint_read, .-bigint_read
	.section	.rodata.str1.1
.LC5:
	.string	"%lx"
.LC6:
	.string	"%0*lx"
	.text
	.p2align 4,,15
	.globl	bigint_print
	.type	bigint_print, @function
bigint_print:
.LFB58:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	leaq	.LC5(%rip), %rsi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbp
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movl	(%rdi), %r12d
	movq	8(%rdi), %rdx
	movl	$1, %edi
	leal	-1(%r12), %eax
	cltq
	movq	(%rdx,%rax,8), %rdx
	leaq	0(,%rax,8), %rbx
	xorl	%eax, %eax
	call	__printf_chk@PLT
	subl	$2, %r12d
	js	.L40
	movslq	%r12d, %rax
	movl	%r12d, %r12d
	subq	$8, %rbx
	subq	%r12, %rax
	leaq	.LC6(%rip), %r12
	leaq	-8(,%rax,8), %r13
	.p2align 4,,10
	.p2align 3
.L41:
	movq	8(%rbp), %rax
	movl	$16, %edx
	movq	%r12, %rsi
	movl	$1, %edi
	movq	(%rax,%rbx), %rcx
	xorl	%eax, %eax
	subq	$8, %rbx
	call	__printf_chk@PLT
	cmpq	%r13, %rbx
	jne	.L41
.L40:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	movl	$10, %edi
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	putchar@PLT
	.cfi_endproc
.LFE58:
	.size	bigint_print, .-bigint_print
	.p2align 4,,15
	.globl	addc_c
	.type	addc_c, @function
addc_c:
.LFB60:
	.cfi_startproc
	movq	(%rdi), %rax
	addq	%rdx, %rsi
	setc	%dl
	movzbl	%dl, %edx
	addq	%rsi, %rax
	cmpq	%rax, %rdx
	seta	%dl
	movzbl	%dl, %edx
	movq	%rdx, (%rdi)
	ret
	.cfi_endproc
.LFE60:
	.size	addc_c, .-addc_c
	.section	.rodata.str1.1
.LC7:
	.string	"i == b->nbuckets - 1"
	.text
	.p2align 4,,15
	.globl	bigint_add
	.type	bigint_add, @function
bigint_add:
.LFB61:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rsi, %r15
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r14
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movl	(%rdi), %r12d
	movl	(%rsi), %ebp
	cmpl	%ebp, %r12d
	jge	.L48
	movl	%r12d, %eax
	movq	%rsi, %r14
	movl	%ebp, %r12d
	movq	%rdi, %r15
	movl	%eax, %ebp
.L48:
	movl	$16, %edi
	call	malloc@PLT
	testq	%rax, %rax
	movq	%rax, %r13
	je	.L68
	movslq	%r12d, %rbx
	leaq	0(,%rbx,8), %rsi
	movq	%rsi, %rdi
	movq	%rsi, 8(%rsp)
	call	malloc@PLT
	testq	%rax, %rax
	movq	%rax, 8(%r13)
	movq	8(%rsp), %rsi
	je	.L69
	testl	%ebp, %ebp
	movl	%r12d, 0(%r13)
	jle	.L51
	leal	-1(%rbp), %edx
	movq	8(%r15), %r9
	movq	8(%r14), %r10
	xorl	%r8d, %r8d
	leaq	8(,%rdx,8), %r11
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L54:
	xorl	%edi, %edi
	movq	(%r10,%rdx), %rcx
	addq	(%r9,%rdx), %rcx
	jc	.L70
.L52:
	addq	%r8, %rcx
	xorl	%r8d, %r8d
	cmpq	%rdi, %rcx
	movq	%rcx, (%rax,%rdx)
	setb	%r8b
	addq	$8, %rdx
	cmpq	%rdx, %r11
	jne	.L54
	cmpl	%ebp, %r12d
	jle	.L59
.L58:
	movslq	%ebp, %rdx
	.p2align 4,,10
	.p2align 3
.L60:
	addq	(%r10,%rdx,8), %r8
	movq	%r8, (%rax,%rdx,8)
	addq	$1, %rdx
	xorl	%r8d, %r8d
	cmpl	%edx, %r12d
	jg	.L60
.L47:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r13, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L51:
	.cfi_restore_state
	testl	%r12d, %r12d
	jle	.L47
	movq	8(%r14), %r10
	xorl	%r8d, %r8d
	xorl	%ebp, %ebp
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L59:
	cmpq	%rdi, %rcx
	jnb	.L47
	leal	1(%r12), %edx
	addq	$8, %rsi
	movq	%rax, %rdi
	movl	%edx, 0(%r13)
	call	realloc@PLT
	testq	%rax, %rax
	movq	%rax, 8(%r13)
	je	.L71
	cmpl	%ebp, %r12d
	jne	.L72
	movq	$1, (%rax,%rbx,8)
	jmp	.L47
.L70:
	movl	$1, %edi
	jmp	.L52
.L69:
	call	bigint_new.part.0
.L68:
	leaq	__PRETTY_FUNCTION__.3499(%rip), %rcx
	leaq	.LC0(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	movl	$14, %edx
	call	__assert_fail@PLT
.L72:
	leaq	__PRETTY_FUNCTION__.3564(%rip), %rcx
	leaq	.LC0(%rip), %rsi
	leaq	.LC7(%rip), %rdi
	movl	$261, %edx
	call	__assert_fail@PLT
.L71:
	leaq	__PRETTY_FUNCTION__.3542(%rip), %rcx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$114, %edx
	call	__assert_fail@PLT
	.cfi_endproc
.LFE61:
	.size	bigint_add, .-bigint_add
	.section	.rodata
	.align 8
	.type	__PRETTY_FUNCTION__.3542, @object
	.size	__PRETTY_FUNCTION__.3542, 12
__PRETTY_FUNCTION__.3542:
	.string	"bigint_grow"
	.align 8
	.type	__PRETTY_FUNCTION__.3564, @object
	.size	__PRETTY_FUNCTION__.3564, 11
__PRETTY_FUNCTION__.3564:
	.string	"bigint_add"
	.align 16
	.type	__PRETTY_FUNCTION__.3509, @object
	.size	__PRETTY_FUNCTION__.3509, 16
__PRETTY_FUNCTION__.3509:
	.string	"hex_digit_value"
	.align 8
	.type	__PRETTY_FUNCTION__.3522, @object
	.size	__PRETTY_FUNCTION__.3522, 12
__PRETTY_FUNCTION__.3522:
	.string	"bigint_read"
	.align 8
	.type	__PRETTY_FUNCTION__.3499, @object
	.size	__PRETTY_FUNCTION__.3499, 11
__PRETTY_FUNCTION__.3499:
	.string	"bigint_new"
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
