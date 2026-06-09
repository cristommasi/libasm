
SYS_WRITE equ 1

section .text
	extern __errno_location
	global ft_write

ft_write:							; ssize_t ft_write(int fd = rdi, const void *buf = rsi, size_t count = rdx) {
									;
	mov		rax, SYS_WRITE			; 	ssize_t res = SYS_WRITE;
	syscall							;	res = syscall(res, fd, buf, count);
	test	rax, rax				; 	if (res < 0)
	js		.error					;		return (error(res));
	ret								;	return (res);
									;
	.error:							;
		push	rbx					;	stack++;
		neg		rax					;	res = -res;
		mov		rbx, rax			;	*stack = res;
		call 	__errno_location	;	char *addr = ___errno_location();
		mov		dword [rax], ebx	;	*addr = (int)(*stack);
		mov		rax, -1				;	res = -1;
		pop		rbx					;	stack--;
		ret							;	return (res);
									; }


	