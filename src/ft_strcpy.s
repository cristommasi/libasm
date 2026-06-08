
section .text
	global ft_strcpy

ft_strcpy:								; char *ft_strcpy(char *dest, const char* src) {
										;
	xor     rax, rax					;	size_t i = 0;
										;
	.loop:								;	while (1) {
		mov     r10b, BYTE [rsi + rax]	;		char temp = *(src + i);
		mov     BYTE [rdi + rax], r10b	;		*(dest + i) = temp;
		cmp     BYTE [rsi + rax], 0		;		if ( *(src + i) == 0)
		je      .break					;			break ;
		inc     rax						;		i++;
		jmp     .loop					;	}
	.break:								;
		mov     rax, rdi				;
		ret								;	return (dest);
										; }