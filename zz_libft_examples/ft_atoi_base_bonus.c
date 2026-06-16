
#include "./nasm_sim.h"

// typedefs to match behaviour -----------------------------------
void			_is_sign(void);
void			_is_whitespace(void);
void			_in_base(void);	
void			_is_num(void);
void			_is_alpha(void);
void			_check_base(void);
void			_skip_whitespace(void);
t_func			is_whitespace	= _is_whitespace;
t_func			in_base			= _in_base;
t_func			is_num			= _is_num;
t_func			is_alpha		= _is_alpha;
t_func			check_base		= _check_base;
t_func			skip_whitespace = _skip_whitespace;

// typedefs to match behaviour -----------------------------------

ssize_t			base_values[255];


void    	_is_whitespace(void) {

    xor(&rax, &rax);

    cmp(rdi, '\t');
    if (je())
		goto yes;

    cmp(rdi, '\r');
    if (je())
		goto yes;

    cmp(rdi, '\n');
    if (je())
		goto yes;

    cmp(rdi, ' ');
    if (je())
		goto yes;

    cmp(rdi, '\f');
    if (je())
		goto yes;

    cmp(rdi, '\v');
    if (je())
		goto yes;
	return  ;
	yes:
    	mov_imm(&rax, 1);
		return  ;
}

void		_is_num(void) {
	
	xor(&rax, &rax);

	cmp(rdi, '0');
	if (jl())
		goto ret;

	cmp(rdi, '9');
	if (jg())
		goto ret;

	mov_imm(&rax, 1);
	return  ; // ret 1
	ret:
		return  ; // ret 0
}

void		_is_alpha(void) {

	xor(&rax, &rax);

	test_low_alpha:

		cmp(rdi, 'a');
		if (jl())
			goto test_high_alpha;

		cmp(rdi, 'z');
		if (jg())
			goto test_high_alpha;

		goto yes;

	test_high_alpha:

		cmp(rdi, 'A');
		if (jl())
			goto no;

		cmp(rdi, 'Z');
		if (jg())
			goto no;

		goto yes;
	
	yes:
		mov_imm(&rax, 1);
		return  ;
	no:
		return  ;
}

void		_in_base(void) {

	xor(&rax, &rax);
	cmp(base_values[rdi], -1);
	if (je())
		goto ret;
	
	mov_imm(&rax, 1);
	return  ;
	ret:
		return  ;
}

void		_check_base(void) {


	xor(&rcx, &rcx);
	xor(&rax, &rax);
	loop:

		cmp(*((char*)rdi + rcx), 0);
		if (je())
			goto ret;
		goto test_if_num;
	
		test_if_num:
			push(&rcx);
			push(&rdi);
			mov_imm(&rdi, *((char*)rdi + rcx));
			call(is_num);
			pop(&rdi);
			pop(&rcx);
			test(rax, rax);
			if (jnz())
				goto test_in_base;
			goto test_if_alpha;

		test_if_alpha:
			push(&rcx);
			push(&rdi);
			mov_imm(&rdi, *((char*)rdi + rcx));
			call(is_alpha);
			pop(&rdi);
			pop(&rcx);
			test(rax, rax);
			if (jnz())
				goto test_in_base;
			goto error;

		test_in_base:

			push(&rcx);
			push(&rdi);
			mov_imm(&rdi, *((char*)rdi + rcx));

			call(in_base);
			pop(&rdi);
			pop(&rcx);
			test(rax, rax);
			
			if (jnz())
				goto error;
			goto assign_base_balue;
		
		assign_base_balue:
			base_values[*((char*)rdi + rcx)] = rcx;
    		inc(&rcx);
    		goto loop;

	ret:
		cmp(rcx, 2);
		if (jl())
			goto error;
		mov_reg(&rax, &rcx);
		return  ;
	
	error:
		mov_imm(&rax, -1);
		return  ;
}

void		_skip_whitespace(void) {

	xor(&rax, &rax);
	mov_imm(&rcx, -1);
	loop:

		inc(&rcx);

		cmp(*((char*)rdi + rcx), 0);
		if (je())
			goto ret;
		

		push(&rcx);
		push(&rdi);
		mov_imm(&rdi, *((char*)rdi + rcx));
		call(is_whitespace);
		pop(&rdi);
		pop(&rcx);
		cmp(rax, 1);
		if (je())
			goto loop;
		
		goto ret;

	ret:
		mov_reg(&rax, &rcx);
		return  ;
}


void		ft_atoi_base(void) {
	
	xor(&rax, &rax);
	xor(&rcx, &rcx);
	xor(&r8, &r8);
	xor(&r9, &r9);
	xor(&r10, &r10);
	base:
		push(&rdi);
		mov_reg(&rdi, &rsi);
		call(check_base);
		pop(&rdi);
		cmp(rax, -1);
		if (je())
			goto error;
		mov_reg(&r8, &rax); // int base = strlen(base);
		goto whitespace;

	whitespace:
		push(&r8);
		push(&rdi);
		call(skip_whitespace);
		pop(&rdi);
		pop(&r8);
		mov_reg(&rcx, &rax); // int i = 0;
		xor(&r10, &r10); // int res = 0;
		goto pos_sign;

	pos_sign:
		mov_imm(&r9, 1); //int sign = 1
		cmp(*((char*)rdi + rcx), '+');
		if (jne())
			goto neg_sign;
		inc(&rcx);
		goto mainloop;
	
	neg_sign:
		cmp(*((char*)rdi + rcx), '-');
		if (jne())
			goto mainloop;
		mov_imm(&r9, -1); //int sign = -1
		inc(&rcx);
		goto mainloop;
	
	 
	mainloop:

		cmp(*((char*)rdi + rcx), 0);
		if (je())
			goto ret;


		push(&r8);
		push(&r9);
		push(&r10);
		push(&rdi);
		mov_imm(&rdi, *((char*)rdi + rcx));
		call(in_base);
		pop(&rdi);
		pop(&r10);
		pop(&r9);
		pop(&r8);
		test(rax, rax);
		if (jz())
			goto ret;
		
		mul(&r10, &r8);
		add(&r10, base_values[*((char *)rdi + rcx)]);
		
		inc(&rcx);
		goto mainloop;

	error:
		mov_imm(&rax, 0);
		return ;
	ret:
		mul(&r10, &r9);
		mov_reg(&rax, &r10);
		return ;
}
