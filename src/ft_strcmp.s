
section .text
	global ft_strcmp

ft_strcmp:								
										
	xor     rax, rax					
										
	.loop:								
		mov     r8b, byte [rdi + rax]	
		mov     r9b, byte [rsi + rax]	
		cmp		r8b, r9b				
		jne		.break					
		cmp		r8b, 0					
		je		.break					
		inc		rax						
		jmp		.loop					
										
	.break:								
		movzx	rax, r8b				
		movzx	r10, r9b				
		sub		rax, r10				
		ret								
										