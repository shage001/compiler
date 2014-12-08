.globl yocomain
yocomain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
//================================
yo_YOCO:
      //--------------------------  6:     #b @ #c!
	movl	20(%esi), %eax
	movl	%eax, 16(%esi)
      //--------------------------  7:     #b @ #a[4]!
	movl	0(%esi), %eax
	movl	%eax, 16(%esi)
      //--------------------------  8:     #b @ #a[7]!
	movl	12(%esi), %eax
	movl	%eax, 16(%esi)
      //-------------------------- 10:     #b @ #a[#c]!
	movl	20(%esi), %eax
	movl	-16(%esi, %eax, 4), %eax
	movl	%eax, 16(%esi)
      //-------------------------- 11:     #b @ #a[#c] + (#a[#d] + (#a[#e] + #a[#f]))!
	movl	20(%esi), %eax
	movl	24(%esi), %ecx
	movl	28(%esi), %edx
	movl	32(%esi), %ebx
	movl	-16(%esi, %edx, 4), %edx
	addl	-16(%esi, %ebx, 4), %edx
	movl	-16(%esi, %ecx, 4), %ecx
	addl	%edx, %ecx
	movl	-16(%esi, %eax, 4), %eax
	addl	%ecx, %eax
	movl	%eax, 16(%esi)
      //-------------------------- 12:     #a[#b] @ 2*#a[#c+1]!
	movl	20(%esi), %eax
	addl	$1, %eax
	movl	$2, %ecx
	imull	-16(%esi, %eax, 4), %ecx
	movl	16(%esi), %eax
	movl	%ecx, -16(%esi, %eax, 4)

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
