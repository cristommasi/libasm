TAB_ASCII equ 9
NEWLINE_ASCII equ 10
VERT_TAB_ASCII equ 11
F_FEED_ASCII equ 12
CAR_RET_ASCII equ 13
SPACE_ASCII equ 32
PLUS_ASCII equ 43
MINUS_ASCII equ 45

section .bss
    base_values resq 255

section .text
    global ft_atoi_base


is_whitespace:

    xor     rax, rax

    cmp     rdi, TAB_ASCII
    je      .yes
    cmp     rdi, NEWLINE_ASCII
    je      .yes
    cmp     rdi, VERT_TAB_ASCII
    je      .yes
    cmp     rdi, F_FEED_ASCII
    je      .yes
    cmp     rdi, CAR_RET_ASCII
    je      .yes
    cmp     rdi, SPACE_ASCII
    je      .yes

    ret

    .yes:
        mov     rax, 1
        ret


is_num:

    xor     rax, rax
    cmp     rdi, '0'
    jl      .no
    cmp     rdi, '9'
    jg      .no
    jmp     .yes

    .yes:
        mov     rax, 1
        ret

    .no:
        ret

is_alpha:

    xor     rax, rax
    
    .test_low_alpha:

        cmp     rdi, 'a'
        jl      .test_high_alpha
        cmp     rdi, 'z'
        jg      .test_high_alpha
        jmp     .yes

    .test_high_alpha:

        cmp     rdi, 'A'
        jl      .no
        cmp     rdi, 'Z'
        jg      .no
        jmp     .yes
    
    .yes:
        mov     rax, 1
        ret
    
    .no:
        ret

in_base:
    
    xor     rax, rax
    cmp     qword [base_values + rdi*8], -1
    je      .ret
    mov     rax, 1

    .ret:
        ret

check_base:

    xor     rax, rax
	xor     rcx, rcx

    .loop:

        mov     al, [rdi + rcx]
        cmp     al, 0
        je      .ret
        jmp     .test_if_num

        .test_if_num:
            push    rdi
            push    rcx
            movzx   rdi, al
            call    is_num
            pop     rcx
            pop     rdi
            test    rax, rax
            jnz     .test_in_base
            jmp     .test_if_alpha

        
        .test_if_alpha:
            push    rdi
            push    rcx
            movzx   rdi, al
            call    is_alpha
            pop     rcx
            pop     rdi
            test    rax, rax
            jnz     .test_in_base
            jmp     .error
        
        .test_in_base:
            push    rdi
            push    rcx
            movzx   rdi, al
            call    in_base
            pop     rcx
            pop     rdi
            test    rax, rax
            jnz     .error
            jmp     .assign_base_value     

        .assign_base_value:
            movzx   rbx, al
            mov     qword [base_values + rbx*8], rcx
            inc     rcx
            jmp     .loop
   
    .ret:
        cmp     rcx, 2
        jl      .error
        mov     rax, rcx
        ret

    .error:
        mov     rax, -1
        ret


skip_whitespace:

    xor     rax, rax
    mov     rcx, -1

    .loop:

        inc     rcx
        mov     al, [rdi + rcx]
        jmp     .test_null

        .test_null:
            
            cmp     al, 0
            je      .ret
            jmp     .test_whitespace

        .test_whitespace:

            push    rcx
            push    rdi
            movzx   rdi, al
            call    is_whitespace
            pop     rdi
            pop     rcx
            cmp     rax, 1
            je      .loop
        
        jmp     .ret
       
    .ret:
        mov     rax, rcx
        ret

ft_atoi_base:

	xor     rax, rax
	xor     rcx, rcx
	xor     r8, r8
	xor     r9, r9
	xor     r10, r10

    .base:

        push    rdi
        mov     rdi, rsi
        call    check_base
        pop     rdi
        cmp     rax, -1
        je      .error
        mov     r8, rax
        jmp     .whitespace

    .whitespace:
        push    r8
        push    rdi
        call    skip_whitespace
        pop     rdi
        pop     r8
        mov     rcx, rax
        xor     r10, r10
        jmp     .pos_sign

    .pos_sign:
        mov     r9, 1
        mov     al, [rdi + rcx]
        cmp     al, PLUS_ASCII
        jne     .neg_sign
        inc     rcx
        jmp     .mainloop

    .neg_sign:
        cmp     al, MINUS_ASCII
        jne     .mainloop
        mov     r9, -1
        inc     rcx
        jmp     .mainloop

    .mainloop:

        mov     al, [rdi + rcx]
        cmp     al, 0
        je      .ret
        jmp     .check_in_base


        .check_in_base:
            push    r8
            push    r9
            push    r10
            push    rdi
            movzx   rdi, al
            call    in_base
            pop     rdi
            pop     r10
            pop     r9
            pop     r8
            test    rax, rax
            jz      .ret
        
        imul    r10, r8
        movzx   rbx, al
        add     r10, qword [base_values + rbx*8]
        inc     rcx
        jmp     .mainloop


    .error:
        mov     rax, 0
        ret

    .ret:
        imul    r10, r9
        mov     rax, r10
        ret
