
section .text
	global ft_strcmp

ft_strcmp:								; int ft_strcmp(const char *s1, const char *s2) {
										;
	xor     rax, rax					;	int i = 0;
										;
	.loop:								;	while (1) {
		mov     r8b, byte [rdi + rax]	;		char temp1 = *(s1 + i);
		mov     r9b, byte [rsi + rax]	;		char temp2 = *(s2 + i);
		cmp		r8b, r9b				;		if (temp1 != temp2)
		jne		.break					;			break ;
		cmp		r8b, 0					;		if (temp1 == 0)
		je		.break					;			break ;
		inc		rax						;		i++;
		jmp		.loop					; 	}
										;
	.break:								;
		movzx	rax, r8b				;	int res = (int)temp1;
		movzx	r10, r9b				;	int res2 = (int)temp2;
		sub		rax, r10				;	res -= res2;
		ret								;	return (res);
										; }