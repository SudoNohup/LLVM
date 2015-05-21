	.file	"inputfile/dcetest-simp.bc"
	.text
	.globl	test1
	.align	16, 0x90
	.type	test1,@function
test1:                                  # @test1
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	leal	3(%eax,%eax), %eax
	popl	%ebp
	ret
.Ltmp0:
	.size	test1, .Ltmp0-test1

	.globl	test2
	.align	16, 0x90
	.type	test2,@function
test2:                                  # @test2
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	movl	$-1, %eax
	movl	8(%ebp), %ecx
	jmp	.LBB1_1
	.align	16, 0x90
.LBB1_2:                                # %for.body
                                        #   in Loop: Header=BB1_1 Depth=1
	leal	3(%ecx,%ecx), %ecx
.LBB1_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	incl	%eax
	cmpl	$999999999, %eax        # imm = 0x3B9AC9FF
	jle	.LBB1_2
# BB#3:                                 # %for.end
	xorl	%eax, %eax
	popl	%ebp
	ret
.Ltmp1:
	.size	test2, .Ltmp1-test2

	.globl	test3
	.align	16, 0x90
	.type	test3,@function
test3:                                  # @test3
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	.align	16, 0x90
.LBB2_1:                                # %do.body
                                        # =>This Inner Loop Header: Depth=1
	incl	%eax
	cmpl	$1000000000, %eax       # imm = 0x3B9ACA00
	jl	.LBB2_1
# BB#2:                                 # %do.end
	popl	%ebp
	ret
.Ltmp2:
	.size	test3, .Ltmp2-test3

	.section	.rodata.cst8,"aM",@progbits,8
	.align	8
.LCPI3_0:
	.quad	4696837146684686336     # double 1.0E+6
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$20, %esp
	calll	clock
	movl	%eax, %esi
	movl	$1, (%esp)
	calll	test1
	movl	$1, (%esp)
	calll	test2
	movl	$1, (%esp)
	calll	test3
	calll	clock
	subl	%esi, %eax
	cvtsi2sdl	%eax, %xmm0
	divsd	.LCPI3_0, %xmm0
	movsd	%xmm0, 4(%esp)
	movl	$.L.str, (%esp)
	calll	printf
	xorl	%eax, %eax
	addl	$20, %esp
	popl	%esi
	popl	%ebp
	ret
.Ltmp3:
	.size	main, .Ltmp3-main

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%f seconds\n"
	.size	.L.str, 12


	.ident	"clang version 3.4 (tags/RELEASE_34/final)"
	.section	".note.GNU-stack","",@progbits
