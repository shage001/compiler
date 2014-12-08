.globl main
main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	movl	$globals, %esi
	call	yo_YOCO
	xorl	%eax, %eax	
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
//================================
yo_swap:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_swap, %esp
      //--------------------------  5:     int #tmp @ #a!
	movl	8(%ebp), %eax
	movl	0(%eax), %eax
	movl	%eax, -16(%ebp)
      //--------------------------  6:     #a @ #b!
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	0(%eax), %eax
	movl	%eax, 0(%ecx)
      //--------------------------  7:     #b @ #tmp!
	movl	12(%ebp), %eax
	movl	-16(%ebp), %ecx
	movl	%ecx, 0(%eax)
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_swap, 4
//================================
yo_bubble:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_bubble, %esp
while5:
      //-------------------------- 11:     while #hi > #lo:
	movl	16(%ebp), %eax
	cmpl	12(%ebp), %eax
	jle	funend4
      //-------------------------- 12:         int #j @ #lo!
	movl	12(%ebp), %eax
	movl	%eax, -16(%ebp)
      //-------------------------- 13:         yono #changed? @ no!
	movl	$0, -20(%ebp)
while9:
      //-------------------------- 14:         while #j < #hi:
	movl	-16(%ebp), %eax
	cmpl	16(%ebp), %eax
	jge	stmt8
      //-------------------------- 15:             if #X[#j] > #X[#j+1]:
	movl	-16(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	-16(%ebp), %edx
	addl	$1, %edx
	movl	8(%ebp), %ebx
	movl	0(%ecx, %eax, 4), %eax
	cmpl	0(%ebx, %edx, 4), %eax
	jle	stmt10
      //-------------------------- 16:                 swap(#X[#j], #X[#j+1])!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	8(%ebp), %ecx
	leal	0(%ecx, %eax, 4), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	movl	8(%ebp), %ecx
	leal	0(%ecx, %eax, 4), %eax
	pushl	%eax
	call	yo_swap
	addl	$8, %esp
      //-------------------------- 17:                 #changed? @ yo!
	movl	$1, -20(%ebp)
stmt10:
      //-------------------------- 19:             #j @ #j + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while9
stmt8:
      //-------------------------- 21:         if not #changed?:
	cmpl	$0, -20(%ebp)
	jne	stmt12
      //-------------------------- 22:             retweet!
	jmp	funend4
stmt12:
      //-------------------------- 24:         #hi @ #hi - 1!
	movl	16(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 16(%ebp)
	jmp	while5
funend4:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_bubble, 8
//================================
yo_YOCO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_YOCO, %esp
      //-------------------------- 30:     #A[1] @  6!
	movl	$6, -32(%ebp)
      //-------------------------- 31:     #A[2] @ -2!
	movl	$-2, -28(%ebp)
      //-------------------------- 32:     #A[3] @ 44!
	movl	$44, -24(%ebp)
      //-------------------------- 33:     #A[4] @  3!
	movl	$3, -20(%ebp)
      //-------------------------- 34:     #A[5] @  5!
	movl	$5, -16(%ebp)
      //-------------------------- 35:     bubble(#A, 1, 5)!
	pushl	$5
	pushl	$1
	leal	-32(%ebp), %eax
	pushl	%eax
	call	yo_bubble
	addl	$12, %esp
      //-------------------------- 36:     put(#A[1])! putc(' ')!
	pushl	-32(%ebp)
	call	yo_put
	addl	$4, %esp
	pushl	$32
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 37:     put(#A[2])! putc(' ')!
	pushl	-28(%ebp)
	call	yo_put
	addl	$4, %esp
	pushl	$32
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 38:     put(#A[3])! putc(' ')!
	pushl	-24(%ebp)
	call	yo_put
	addl	$4, %esp
	pushl	$32
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 39:     put(#A[4])! putc(' ')!
	pushl	-20(%ebp)
	call	yo_put
	addl	$4, %esp
	pushl	$32
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 40:     put(#A[5])! putc('\n')!
	pushl	-16(%ebp)
	call	yo_put
	addl	$4, %esp
	pushl	$10
	call	yo_putc
	addl	$4, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_YOCO, 20
//================================
yo_put:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	8(%ebp)	
	pushl	$intStr
	call	printf	
	leave	
	ret	
//================================
yo_get:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp	
	leal	-4(%ebp), %eax	
	pushl	%eax	
	pushl	$intStr
	call	scanf	
	movl	-4(%ebp), %eax	
	leave	
	ret	
//================================
yo_putc:
	jmp	putchar	
//================================
yo_getc:
	jmp	getchar	

.section	.rodata
intStr: .string "%d"

.section	.data
globals: .space 1
