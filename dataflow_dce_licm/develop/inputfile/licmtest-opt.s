	.file	"inputfile/licmtest-opt.bc"
	.text
	.globl	test1
	.align	16, 0x90
	.type	test1,@function
test1:                                  # @test1
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	movl	$-100, %eax
	movl	$-1, %ecx
	movl	12(%ebp), %edx
	addl	8(%ebp), %edx
	jmp	.LBB0_1
	.align	16, 0x90
.LBB0_2:                                # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	%edx, %eax
.LBB0_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	incl	%ecx
	cmpl	$-2, %ecx
	jle	.LBB0_2
# BB#3:                                 # %for.end
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
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	.align	16, 0x90
.LBB1_1:                                # %do.body
                                        # =>This Inner Loop Header: Depth=1
	cmpl	%eax, %ecx
	jge	.LBB1_3
# BB#2:                                 # %if.then
                                        #   in Loop: Header=BB1_1 Depth=1
	incl	%ecx
.LBB1_3:                                # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	decl	%eax
	cmpl	$8, %eax
	jg	.LBB1_1
# BB#4:                                 # %do.end
	movl	$4, %eax
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
	movl	$1, %eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	.align	16, 0x90
.LBB2_1:                                # %do.body
                                        # =>This Inner Loop Header: Depth=1
	cmpl	%ecx, %edx
	jge	.LBB2_3
# BB#2:                                 # %if.then
                                        #   in Loop: Header=BB2_1 Depth=1
	incl	%edx
	movl	$2, %eax
.LBB2_3:                                # %if.end
                                        #   in Loop: Header=BB2_1 Depth=1
	decl	%ecx
	cmpl	$8, %ecx
	jg	.LBB2_1
# BB#4:                                 # %do.end
	popl	%ebp
	ret
.Ltmp2:
	.size	test3, .Ltmp2-test3

	.globl	test4
	.align	16, 0x90
	.type	test4,@function
test4:                                  # @test4
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8000000, %esp          # imm = 0x7A1200
	movl	12(%ebp), %ecx
	xorl	%edx, %edx
	imull	8(%ebp), %ecx
	xorl	%eax, %eax
	jmp	.LBB3_1
	.align	16, 0x90
.LBB3_2:                                # %while.body
                                        #   in Loop: Header=BB3_1 Depth=1
	movl	%ecx, -7999996(%ebp,%edx,4)
	incl	%edx
	movl	%ecx, %eax
.LBB3_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$999999, %edx           # imm = 0xF423F
	jle	.LBB3_2
# BB#3:                                 # %while.end
	addl	$8000000, %esp          # imm = 0x7A1200
	popl	%ebp
	ret
.Ltmp3:
	.size	test4, .Ltmp3-test4

	.globl	test5
	.align	16, 0x90
	.type	test5,@function
test5:                                  # @test5
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8000000, %esp          # imm = 0x7A1200
	movl	8(%ebp), %eax
	imull	12(%ebp), %eax
	xorl	%ecx, %ecx
	.align	16, 0x90
.LBB4_1:                                # %do.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	%eax, -7999996(%ebp,%ecx,4)
	leal	1(%ecx), %ecx
	cmpl	$1000000, %ecx          # imm = 0xF4240
	jl	.LBB4_1
# BB#2:                                 # %do.end
	addl	$8000000, %esp          # imm = 0x7A1200
	popl	%ebp
	ret
.Ltmp4:
	.size	test5, .Ltmp4-test5

	.globl	test6
	.align	16, 0x90
	.type	test6,@function
test6:                                  # @test6
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	movl	8(%ebp), %eax
	incl	%eax
	.align	16, 0x90
.LBB5_1:                                # %do.cond
                                        # =>This Inner Loop Header: Depth=1
	decl	%ecx
	testl	%ecx, %ecx
	jg	.LBB5_1
# BB#2:                                 # %do.cond3
                                        #   in Loop: Header=BB5_1 Depth=1
	testl	%ecx, %ecx
	leal	-1(%ecx), %ecx
	jg	.LBB5_1
# BB#3:                                 # %do.end6
	popl	%ebp
	ret
.Ltmp5:
	.size	test6, .Ltmp5-test6

	.globl	test7
	.align	16, 0x90
	.type	test7,@function
test7:                                  # @test7
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	movl	$-1, %ecx
	movl	8(%ebp), %eax
	incl	%eax
	.align	16, 0x90
.LBB6_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	incl	%ecx
	cmpl	$999999999, %ecx        # imm = 0x3B9AC9FF
	jle	.LBB6_1
# BB#2:                                 # %for.end
	popl	%ebp
	ret
.Ltmp6:
	.size	test7, .Ltmp6-test7

	.globl	test8
	.align	16, 0x90
	.type	test8,@function
test8:                                  # @test8
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	subl	$400, %esp              # imm = 0x190
	movl	8(%ebp), %eax
	imull	12(%ebp), %eax
	xorl	%ecx, %ecx
	.align	16, 0x90
.LBB7_1:                                # %do.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	%eax, -396(%ebp,%ecx,8)
	movl	$0, -396(%ebp,%ecx,4)
	leal	1(%ecx), %ecx
	cmpl	$20, %ecx
	jl	.LBB7_1
# BB#2:                                 # %do.end
	xorl	%eax, %eax
	addl	$400, %esp              # imm = 0x190
	popl	%ebp
	ret
.Ltmp7:
	.size	test8, .Ltmp7-test8

	.globl	test9
	.align	16, 0x90
	.type	test9,@function
test9:                                  # @test9
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	subl	$400, %esp              # imm = 0x190
	movl	8(%ebp), %eax
	imull	12(%ebp), %eax
	xorl	%ecx, %ecx
	.align	16, 0x90
.LBB8_1:                                # %do.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	%eax, -396(%ebp,%ecx,4)
	leal	1(%ecx), %ecx
	cmpl	$20, %ecx
	movl	$0, -400(%ebp)
	jl	.LBB8_1
# BB#2:                                 # %do.end
	xorl	%eax, %eax
	addl	$400, %esp              # imm = 0x190
	popl	%ebp
	ret
.Ltmp8:
	.size	test9, .Ltmp8-test9

	.section	.rodata.cst8,"aM",@progbits,8
	.align	8
.LCPI9_0:
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
	movl	$2, 4(%esp)
	movl	$1, (%esp)
	calll	test1
	movl	$100000000, 4(%esp)     # imm = 0x5F5E100
	movl	$2, (%esp)
	calll	test2
	movl	$100000000, 4(%esp)     # imm = 0x5F5E100
	movl	$2, (%esp)
	calll	test3
	movl	$4, 4(%esp)
	movl	$3, (%esp)
	calll	test4
	movl	$4, 4(%esp)
	movl	$3, (%esp)
	calll	test5
	movl	$1000000000, 4(%esp)    # imm = 0x3B9ACA00
	movl	$0, (%esp)
	calll	test6
	movl	$10, (%esp)
	calll	test7
	movl	$4, 4(%esp)
	movl	$3, (%esp)
	calll	test8
	movl	$4, 4(%esp)
	movl	$3, (%esp)
	calll	test9
	calll	clock
	subl	%esi, %eax
	cvtsi2sdl	%eax, %xmm0
	divsd	.LCPI9_0, %xmm0
	movsd	%xmm0, 4(%esp)
	movl	$.L.str, (%esp)
	calll	printf
	xorl	%eax, %eax
	addl	$20, %esp
	popl	%esi
	popl	%ebp
	ret
.Ltmp9:
	.size	main, .Ltmp9-main

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%f seconds\n"
	.size	.L.str, 12


	.ident	"clang version 3.4 (tags/RELEASE_34/final)"
	.section	".note.GNU-stack","",@progbits
