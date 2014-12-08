.globl yocomain
yocomain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
//================================
yo_YOCO:
      //--------------------------  6: 	#a @ 1!
	movl	$1, 0(%esi)
//freeing memory temp at disp 0
//freeing memory temp at disp 0
      //--------------------------  7: 	#c[2] @ 5!
	movl	$2, %eax
//freeing memory temp at disp 0