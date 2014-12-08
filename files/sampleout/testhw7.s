.globl yocomain
yocomain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
//================================
yo_p:
      //--------------------------  9:     #globalvar @ 1!
	movl	$1, 16(%esi)
      //-------------------------- 10:     #localvar @ 2!
	movl	$2, -16(%ebp)
      //-------------------------- 11:     #valparam @ 3!
	movl	$3, 8(%ebp)
      //-------------------------- 12:     #refparam @ 4!
	movl	12(%ebp), %eax
	movl	$4, 0(%eax)
      //-------------------------- 13:     #globalarr[#valparam] @ 5!
	movl	8(%ebp), %eax
	movl	$5, -12(%esi, %eax, 4)
      //-------------------------- 14:     #localarr[#valparam] @ 6!
	movl	8(%ebp), %eax
	movl	$6, -60(%ebp, %eax, 4)
      //-------------------------- 15:     #paramarr[2 * #valparam] @ 2*3 + 4*5!
	movl	$2, %eax
	imull	8(%ebp), %eax
	movl	16(%ebp), %ecx
	movl	$26, 0(%ecx, %eax, 4)
      //-------------------------- 16:     #localarr[7] @ #refparam / #globalvar!
	movl	12(%ebp), %eax
	movl	0(%eax), %eax
	cltd	
	idivl	16(%esi)
	movl	%eax, -32(%ebp)
//================================
yo_YOCO:

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
