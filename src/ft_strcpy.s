
section .text
	global ft_strcpy

ft_strcpy:								
										
	xor     rax, rax					
										
	.loop:								
		mov     r8b, byte [rsi + rax]	
		mov     byte [rdi + rax], r8b	
		cmp     byte [rsi + rax], 0		
		je      .break					
		inc     rax						
		jmp     .loop					
										
	.break:								
		mov     rax, rdi				
		ret								
										