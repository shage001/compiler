.globl yocomain
yocomain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
//================================
yo_f:
      //--------------------------  5:     int #count @ 0!
	movl	$0, -16(%ebp)
loop4:
      //--------------------------  6:     while #x > 1:
	cmpl	$1, 8(%ebp)
	jle	stmt3
      //--------------------------  7:         #count @ #count + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
      //--------------------------  8:         if #x % 2 like 0:
	movl	8(%ebp), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	cmpl	$0, %edx
	jne	else6
      //--------------------------  9:             #x @ #x / 2!
	movl	8(%ebp), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	movl	%eax, 8(%ebp)
	jmp	loop4
else6:
      //-------------------------- 11:             #x @ 3 * #x + 1!
	movl	$3, %eax
	imull	8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, 8(%ebp)
	jmp	loop4
stmt3:
      //-------------------------- 14:     retweet #count!
	movl	-16(%ebp), %eax

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
