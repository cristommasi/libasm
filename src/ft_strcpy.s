
section .text
	global ft_strcpy

ft_strcpy:								; char *ft_strcpy(char *dest, const char* src) {
										;
	xor     rax, rax					;	size_t i = 0;
										;
	.loop:								;	while (1) {
		mov     r8b, byte [rsi + rax]	;		char temp = *(src + i);
		mov     byte [rdi + rax], r8b	;		*(dest + i) = temp;
		cmp     byte [rsi + rax], 0		;		if ( *(src + i) == 0)
		je      .break					;			break ;
		inc     rax						;		i++;
		jmp     .loop					;	}
										;
	.break:								;
		mov     rax, rdi				;
		ret								;	return (dest);
										; }