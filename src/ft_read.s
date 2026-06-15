
section .text
extern __errno_location
    global ft_read


ft_read:							    	; ssize_t read(int fd = rdi, void *buf = rsi, size_t count = rdx); {
									    	;
	mov		rax, 0					    	; 	ssize_t res = SYS_READ;
	syscall							    	;	res = syscall(res, fd, buf, count);
	test	rax, rax				    	; 	if (res < 0)
	js		.error					    	;		return (error(res));
	ret								    	;	return (res);
                                        	; }
											;
	.error:							        ; ssize_t error(ssize_t res) {
	                                        ;
		push	rbx					        ;	stack++;
		neg		eax					        ;	(int)res = (int)-res;
		mov		ebx, eax			        ;	(int)(*stack) = (int)res;
		call 	__errno_location wrt ..plt	;	char *err_addr = ___errno_location();
		mov		dword [rax], ebx	        ;	*err_addr = (int)(*stack);
		mov		rax, -1				        ;	res = -1;
		pop		rbx					        ;	stack--;
		ret							        ;	return (res);
										    ; }



    
    