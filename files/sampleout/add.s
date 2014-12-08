.globl yocomain
yocomain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
//================================
yo_YOCO:
      //--------------------------  4:     #a @ #b!
	movl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
      //--------------------------  5:     #a @ 1!
	movl	$1, -16(%ebp)
      //--------------------------  6:     #a @ #b + #c!
	movl	-20(%ebp), %eax
	addl	-24(%ebp), %eax
	movl	%eax, -16(%ebp)
      //--------------------------  7:     #a @ 2 + #b!
	movl	$2, %eax
	addl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
      //--------------------------  8:     #a @ 2 + 3 + #b!
	movl	$5, %eax
	addl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
      //--------------------------  9:     #a @ #b + 2 + 3!
	movl	-20(%ebp), %eax
	addl	$2, %eax
	addl	$3, %eax
	movl	%eax, -16(%ebp)
      //-------------------------- 10:     #a @ #b + (2 + 3)!
	movl	-20(%ebp), %eax
	addl	$5, %eax
	movl	%eax, -16(%ebp)
      //-------------------------- 11:     #a @ #b + #b + #b + #b + #b!
	movl	-20(%ebp), %eax
	addl	-20(%ebp), %eax
	addl	-20(%ebp), %eax
	addl	-20(%ebp), %eax
	addl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
      //-------------------------- 12:     #a @ 2*#b + (3*#b + (4*#b + (5*#b + (6*#b + 7*#b))))!
	movl	$2, %eax
	imull	-20(%ebp), %eax
	movl	$3, %ecx
	imull	-20(%ebp), %ecx
	movl	$4, %edx
	imull	-20(%ebp), %edx
	movl	$5, %ebx
	imull	-20(%ebp), %ebx
	movl	$6, %edi
	imull	-20(%ebp), %edi
//creating new memtemp at disp -28
	movl	%eax, -28(%ebp)
	movl	$7, %eax
	imull	-20(%ebp), %eax
	addl	%eax, %edi
	addl	%edi, %ebx
	addl	%ebx, %edx
	addl	%edx, %ecx
	movl	-28(%ebp), %eax
//freeing memory temp at disp -28
	addl	%ecx, %eax
	movl	%eax, -16(%ebp)
      //-------------------------- 13:     #a @ 2*#b + (3*#b + (4*#b + (5*#b + (6*#b + (7*#b + 8*#b)))))!
	movl	$2, %eax
	imull	-20(%ebp), %eax
	movl	$3, %ecx
	imull	-20(%ebp), %ecx
	movl	$4, %edx
	imull	-20(%ebp), %edx
	movl	$5, %ebx
	imull	-20(%ebp), %ebx
	movl	$6, %edi
	imull	-20(%ebp), %edi
//reusing memtemp at disp -28
	movl	%eax, -28(%ebp)
	movl	$7, %eax
	imull	-20(%ebp), %eax
//creating new memtemp at disp -32
	movl	%eax, -32(%ebp)
	movl	$8, %eax
	imull	-20(%ebp), %eax
//creating new memtemp at disp -36
	movl	%eax, -36(%ebp)
	movl	-32(%ebp), %eax
//freeing memory temp at disp -32
	addl	-36(%ebp), %eax
//freeing memory temp at disp -36
	addl	%eax, %edi
	addl	%edi, %ebx
	addl	%ebx, %edx
	addl	%edx, %ecx
	movl	-28(%ebp), %eax
//freeing memory temp at disp -28
	addl	%ecx, %eax
	movl	%eax, -16(%ebp)

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
