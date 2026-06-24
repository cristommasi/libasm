
section .text
	extern __errno_location
	global ft_write

ft_write:							      
									      
	mov		rax, 1					      
	syscall							      
	test	rax, rax				      
	js		.error					      
	ret								      
                                          

	.error:							      
	                                      
		push	rbx					      
		neg		eax					      
		mov		ebx, eax			      
		call 	__errno_location wrt ..plt
		mov		dword [rax], ebx	      
		mov		rax, -1				      
		pop		rbx					      
		ret							      
									      
	