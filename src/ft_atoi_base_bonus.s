

section .text
    global ft_atoi_base

get_sign:

    .prologue:
       push    rbp
       mov     rbp, rsp
       push    rbx
       push    r12

    .init:
        mov     r12, rdi
        xor     rbx, rbx
        mov     rax, 1

    .compare:
        movzx   rdi, byte [r12]
        cmp     dil, 43 ; '+'
        je      .positive
        cmp     dil, 45 ; '-'
        je      .negative
        jmp     .epilogue

    .positive:
        mov     rax, 1
        inc     rbx
        jmp     .epilogue

    .negative:
        mov     rax, -1
        inc     rbx
    
    .epilogue:
        mov     rdx, rbx
        pop     r12
        pop     rbx
        pop     rbp
        ret
        
;------------------------------------------
;------------------------------------------
is_whitespace:

    .prologue:
        push    rbp
        mov     rbp, rsp
    .init:
        xor     rax, rax
    .compare:
        cmp     edi, 9  ; '/t'
        je      .yes
        cmp     edi, 10 ; '/n' 
        je      .yes
        cmp     edi, 11 ; '/v'
        je      .yes
        cmp     edi, 12 ; '/f'
        je      .yes
        cmp     edi, 13 ; '/r'
        je      .yes
        cmp     edi, 32 ; ' '
        je      .yes
        jmp     .epilogue

    .yes:
        mov     rax, 1
    .epilogue:
        pop     rbp
        ret
;------------------------------------------
;------------------------------------------
is_num:

    .prologue:
        push    rbp
        mov     rbp, rsp
    .init:
        xor     rax, rax
    .check:
        cmp     rdi, 48 ; '0'
        jl      .epilogue
        cmp     rdi, 57 ; '9'
        jg      .epilogue
        mov     rax, 1
    .epilogue:
        pop rbp
        ret
;------------------------------------------
;------------------------------------------
is_alpha:

    .prologue:
        push    rbp
        mov     rbp, rsp
    .init:
        xor     rax, rax
    
    .test_low_alpha:
        cmp     rdi, 97 ; 'a'
        jl      .test_high_alpha
        cmp     rdi, 122 ; 'z'
        jg      .test_high_alpha
        mov     rax, 1
        jmp     .epilogue

    .test_high_alpha:

        cmp     rdi, 65 ; 'A'
        jl      .epilogue
        cmp     rdi, 90 ; 'Z'
        jg      .epilogue
        mov     rax, 1

    .epilogue:
        pop rbp
        ret
;------------------------------------------
;------------------------------------------
in_base:

    .prologue:
        push    rbp
        mov     rbp, rsp

    .init:
        xor     rax, rax

    .compare:
        cmp     qword [rsi + rdi*8], -1
        je      .epilogue
        mov     rax, 1
    
    .epilogue:
        pop rbp
        ret
;------------------------------------------
;------------------------------------------
skip_whitespace:

    .prologue:
        push    rbp
        mov     rbp, rsp
        push    rbx
        push    r12

    .init:
        xor     rbx, rbx ; int i
        mov     r12, rdi ; char *str
        xor     rax, rax

    .loop:

        movzx   rdi, byte [r12 + rbx]
        cmp     byte [r12 + rbx], 0
        je      .epilogue

        .test_whitespace:

            call    is_whitespace
            test    rax, rax
            jz      .epilogue
            
        inc     rbx
        jmp     .loop
       
    .epilogue:
        mov     rax, rbx
        pop     r12
        pop     rbx
        pop     rbp
        ret
;------------------------------------------
;------------------------------------------
get_base:

    .prologue:
        push    rbp
        mov     rbp, rsp
        push    r15
        push    r14
        push    r13
        push    r12
        
    
    .init:
        mov     r12, rsi    ; size_t base_values[256]
        mov     r13, rdi    ; char *base
        mov     r15, 0      ; int i = 0
        mov     r14, 0      ; char c = base[i]

    .loop:

        movzx   r14, byte [r13 + r15]
        cmp     r14, 0
        je      .ret

        .test_if_num:
            
            mov     rdi, r14
            call    is_num
            test    rax, rax
            jnz     .test_in_base
        
        .test_if_alpha:
            
            mov     rdi, r14
            call    is_alpha
            test    rax, rax
            jnz     .test_in_base
            jmp     .error
        
        .test_in_base:
            mov     rdi, r14
            mov     rsi, r12
            call    in_base
            test    rax, rax
            jnz     .error 

        .assign_base_value:
            mov     qword [r12 + r14*8], r15 ; base_value[base[i]] = i
            inc     r15
            jmp     .loop

    .ret:
        mov     rax, r15
        cmp     rax, 2
        jl      .error
        jmp     .epilogue

    .error:
        mov     rax, -1

    .epilogue:
        pop     r12
        pop     r13
        pop     r14
        pop     r15
        pop     rbp
        ret

    
;------------------------------------------
;------------------------------------------
init_base_values:

    .prologue:
        push    rbp
        mov     rbp, rsp
    .init:
        mov     rcx, 256
    .fill:
        mov     qword [rdi + rcx*8 - 8], -1
        dec     rcx
        jnz     .fill
    .epilogue:
        pop     rbp
        ret

;------------------------------------------
;------------------------------------------
ft_atoi_base:

    .prologue:
        push    rbp
        mov     rbp, rsp
        push    r15        ; int sign
        push    r14        ; int res
        push    r13        ; char *base / base_len
        push    r12        ; char *str
        sub     rsp, 256*8 ; size_t base_values[256]

    .init:
        mov     r15, 1
        mov     r14, 0
        mov     r13, rsi
        mov     r12, rdi
        xor     rbx, rbx
        mov     rdi, rsp
        call    init_base_values ; init_base_values(char base_values[255])

    .base:

        mov     rdi, r13
        mov     rsi, rsp
        call    get_base ; get_base(char *base, char base_values[255])
        cmp     rax, -1
        je      .error
        mov     r13, rax ; base_len = x

    .whitespace:
        mov     rdi, r12
        call    skip_whitespace ; skip_whitespace(char *str)
        add     r12, rax ; str + rax OR str[i + rax]
        

    .sign:
        mov     rdi, r12
        call    get_sign ; get_sign(char *str)
        mov     r15, rax ; sign = rax
        add     r12, rdx ; str + rbx
        xor     rbx, rbx

    .mainloop:

        movzx   rdi, byte [r12 + rbx]
        cmp     byte [r12 + rbx], 0
        je      .epilogue
        
        .check_in_base:

            mov     rsi, rsp
            call    in_base
            test    rax, rax
            jz      .epilogue
        
        imul    r14, r13
        movzx   rdi, byte [r12 + rbx]
        add     r14, qword [rsp + rdi*8]
        inc     rbx
        jmp     .mainloop


    .error:
        mov     r14, 0
        jmp     .epilogue

    .epilogue:
        imul    r14, r15
        mov     eax, r14d
        add     rsp, 256*8 ; size_t base_values[256]
        pop     r12
        pop     r13
        pop     r14
        pop     r15
        pop     rbp
        ret
;------------------------------------------
;------------------------------------------