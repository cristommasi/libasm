section .text
	global  ft_strlen

ft_strlen:							; size_t ft_strlen(const char *s) {
									;
	xor     rax, rax                ;	size_t i = 0;
									;
	.loop:                          ;	while (1) {
		cmp     BYTE [rdi + rax], 0 ;		if ( *(s + i) == 0)
		je      .break             	;			break ;
		inc     rax                 ;		i++;
		jmp     .loop               ;	}
	.break:							;
		ret                         ;	return (i);
									; }