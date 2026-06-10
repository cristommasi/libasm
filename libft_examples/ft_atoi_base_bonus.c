
#include "./nasm_sim.h"

// typedefs to match behaviour -----------------------------------
void			_is_sign(void);
void			_is_whitespace(void);
void			_in_base(void);	
void			_is_num(void);
void			_is_low_alpha(void);
void			_is_high_alpha(void);
void			_check_base(void);
void			_skip_whitespace(void);
void			_set_sign(void);
t_func			is_sign 		= _is_sign;
t_func			is_whitespace	= _is_whitespace;
t_func			in_base			= _in_base;
t_func			is_num			= _is_num;
t_func			is_low_alpha	= _is_low_alpha;
t_func			is_high_alpha	= _is_high_alpha;
t_func			check_base		= _check_base;
t_func			skip_whitespace = _skip_whitespace;
t_func			set_sign = _set_sign;

// typedefs to match behaviour -----------------------------------

ssize_t			base_values[255];
const char		*str;
const char		*base;

void		_is_sign(void) {

	xor(&rax, &rax);

	cmp(rsi, '+');
    if (je())
		goto yes;

	cmp(rsi, '-');
    if (je())
		goto yes;
	return ;
	yes:
		mov_imm(&rax, 1);
		return ;
}

void    	_is_whitespace(void) {

    xor(&rax, &rax);

    cmp(rsi, '\t');
    if (je())
		goto yes;

    cmp(rsi, '\r');
    if (je())
		goto yes;

    cmp(rsi, '\n');
    if (je())
		goto yes;

    cmp(rsi, ' ');
    if (je())
		goto yes;

    cmp(rsi, '\f');
    if (je())
		goto yes;

    cmp(rsi, '\v');
    if (je())
		goto yes;
	return ;
	yes:
    	mov_imm(&rax, 1);
		return ;
}

void		_is_num(void) {
	
	xor(&rax, &rax);

	cmp(rsi, '0');
	if (jl())
		goto ret;

	cmp(rsi, '9');
	if (jg())
		goto ret;

	mov_imm(&rax, 1);
	return ;
	ret:
		return ;
}

void		_is_low_alpha(void) {

	xor(&rax, &rax);

	cmp(rsi, 'a');
	if (jl())
		goto ret;

	cmp(rsi, 'z');
	if (jg())
		goto ret;

	mov_imm(&rax, 1);
	return ;
	ret:
		return ;
}

void		_is_high_alpha(void) {
	
	xor(&rax, &rax);

	cmp(rsi, 'A');
	if (jl())
		goto ret;

	cmp(rsi, 'Z');
	if (jg())
		goto ret;

	mov_imm(&rax, 1);
	return ;
	ret:
		return ;
}

void		_in_base(void) {

	xor(&rax, &rax);
	cmp(base_values[rsi], -1);
	if (je())
		goto ret;
	mov_imm(&rax, 1);
	ret:
		return ;
}

void		_check_base(void) {

	xor(&rsi, &rsi);
	xor(&rcx, &rcx);
	xor(&rax, &rax);
	loop:

		mov_imm(&rsi, *(base + rcx));
		cmp(rsi, 0);
		if (je())
			goto ret;

		call(is_num);
		test(rax, rax);
		if (jnz())
			goto test_in_base;

		call(is_low_alpha);
		test(rax, rax);
		if (jnz())
			goto test_in_base;

		call(is_high_alpha);
		test(rax, rax);
		if (jnz())
			goto test_in_base;
		
		goto error;

	test_in_base:
		
		call(in_base);
		test(rax, rax);
		if (jnz())
			goto error;
		base_values[rsi] = rcx;
    	inc(&rcx);
    	goto loop;
		

	ret:
		cmp(rcx, 2);
		if (jl())
			goto error;
		mov_reg(&rax, &rcx);
		return ;
	
	error:
		mov_imm(&rax, -1);
		return ;
}

void		_skip_whitespace(void) {

	goto loop;

	loop:

		inc(&rcx);
		mov_imm(&rsi, *(str + rcx));
		cmp(rsi, 0);
		if (je())
			goto ret;
		call(is_whitespace);
		cmp(rax, 1);
		if (je())
			goto loop;
		goto ret;

	ret:
		return ;
}

void		_set_sign(void) {

	goto test_pos_sign;

	test_pos_sign:
		mov_imm(&r9, 1); //int sign = 1
		cmp(*(str + rcx), '+');
		if (jne())
			goto test_neg_sign;
		inc(&rcx);
		goto ret;
	
	test_neg_sign:
		cmp(*(str + rcx), '-');
		if (jne())
			goto ret;
		mov_imm(&r9, -1); //int sign = -1
		inc(&rcx);
		goto ret;
	ret:
		return ;
}

void		ft_atoi_base(void) {
	
	call(check_base);
	cmp(rax, -1);
	if (je())
		goto error;
	
	mov_reg(&r8, &rax); // int base = strlen(base);
	xor(&rax, &rax); // 0
	xor(&r10, &r10); // 0
	mov_imm(&rcx, -1); // int i = -1
	

	call(skip_whitespace);
	call(set_sign);
	
	mainloop:
	
		mov_imm(&rsi, *(str + rcx));
		cmp(rsi, 0);
		if (je())
			goto ret;

		call(in_base);
		test(rax, rax);
		if (jz())
			goto ret;

		mul(&r10, &r8);
		add(&r10, base_values[rsi]);
		
		inc(&rcx);
		cmp(r10, INT_MAX);
		if (jg()) goto overflow;
		cmp(r10, INT_MIN);
		if (jl()) goto underflow;
		goto mainloop;

	overflow:
		mov_imm(&rax, INT_MIN);
		return ;
	underflow:
		mov_imm(&rax, INT_MAX);
		return ;
	error:
		mov_imm(&rax, 0);
		return ;
	ret:
		mul(&r10, &r9);
		mov_reg(&rax, &r10);
		return ;
}

int main(void) {


	for (int i = 0; i < 255; i++) {
		base_values[i] = -1;
	}

	str = "76";
	base = "0123456789";
	ft_atoi_base();
	printf("num  = %ld \n", rax);
	printf("atoi = %d \n", atoi(str));
	
	return 0;
}