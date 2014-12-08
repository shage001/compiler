.globl yocomain
yocomain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
//================================
yo_YOCO:
      //--------------------------  6:     #b @ 9!
	movl	$9, -48(%ebp)
      //--------------------------  7:     #c @ 4!
	movl	$4, -52(%ebp)
      //--------------------------  8:     #a[#b / #c + #b % #c] @ 1!
	movl	-48(%ebp), %eax
	cltd	
	idivl	-52(%ebp)
//making reg eax available
	movl	%eax, %ecx
	movl	-48(%ebp), %eax
	cltd	
	idivl	-52(%ebp)
	addl	%edx, %ecx
	movl	$1, -52(%ebp, %ecx, 4)
      //--------------------------  9:     #a[#c] @ #a[#a[#b/#c] % 2*#a[(2+#b)/(3+#c)]]!
	movl	-48(%ebp), %eax
	cltd	
	idivl	-52(%ebp)
	movl	-52(%ebp, %eax, 4), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	movl	$2, %eax
	addl	-48(%ebp), %eax
	movl	$3, %ecx
	addl	-52(%ebp), %ecx
//making reg edx available
	movl	%edx, %ebx
	cltd	
	idivl	%ecx
	imull	-52(%ebp, %eax, 4), %ebx
	movl	-52(%ebp), %eax
	movl	-52(%ebp, %ebx, 4), %ecx
	movl	%ecx, -52(%ebp, %eax, 4)
      //-------------------------- 10:     #a[#b] @ #c!
	movl	-48(%ebp), %eax
	movl	-52(%ebp), %ecx
	movl	%ecx, -52(%ebp, %eax, 4)
      //-------------------------- 11:     #c @ #a[#b] + (#a[#b] + (#a[#b] + (#a[#b] + (#a[#b] + (#a[#b] + 2*#b)))))!
	movl	-48(%ebp), %eax
	movl	-48(%ebp), %ecx
	movl	-48(%ebp), %edx
	movl	-48(%ebp), %ebx
	movl	-48(%ebp), %edi
//creating new memtemp at disp -56
	movl	-52(%ebp, %eax, 4), %eax
	movl	%eax, -56(%ebp)
	movl	-48(%ebp), %eax
//creating new memtemp at disp -60
	movl	-52(%ebp, %eax, 4), %eax
	movl	%eax, -60(%ebp)
	movl	$2, %eax
	imull	-48(%ebp), %eax
//creating new memtemp at disp -64
	movl	%eax, -64(%ebp)
	movl	-60(%ebp), %eax
//freeing memory temp at disp -60
	addl	-64(%ebp), %eax
//freeing memory temp at disp -64
	movl	-52(%ebp, %edi, 4), %edi
	addl	%eax, %edi
	movl	-52(%ebp, %ebx, 4), %eax
	addl	%edi, %eax
	movl	-52(%ebp, %edx, 4), %edx
	addl	%eax, %edx
	movl	-52(%ebp, %ecx, 4), %eax
	addl	%edx, %eax
	movl	-56(%ebp), %ecx
//freeing memory temp at disp -56
	addl	%eax, %ecx
	movl	%ecx, -52(%ebp)
      //-------------------------- 12:     #c @ #c!  // output should be 42
	movl	-52(%ebp), %eax
	movl	%eax, -52(%ebp)

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
