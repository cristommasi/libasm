%include "libasm_bonus.inc"

section .text
    global ft_atoi_base

init_base_values:

    mov     r10, 256
    
    .fill:
        dec     r10
        mov     qword [rdi + r10*8], -1
        test    r10, r10
        jnz     .fill
        
    ret
;------------------------------------------
;------------------------------------------
ft_atoi_base:
    
    stack_enter
    stack_u64       string              ; char *str
    stack_u64       base                ; char *base / base_len
    stack_u64       sign                ; int sign
    stack_u64       res                 ; int res
    stack_arr_u64   base_values, 256    ; size_t base_values[256]
    stack_alloc

    .check_null:
        test rdi, rdi
        jz  .error
        test rsi, rsi
        jz .error

    .init:
        mov     string, rdi
        mov     base, rsi
        mov     sign, 1
        mov     res, 0
        lea     rdi, [base_values]
        call    init_base_values ; init_base_values(char base_values[255])

    .base:
        mov     rdi, base
        lea     rsi, [base_values]
        call    get_base ; get_base(char *base, char base_values[255])
        cmp     rax, -1
        je      .error
        mov     base, rax ; base_len = x ; pre r13


    .whitespace:
        mov     rdi, string
        call    skip_whitespace ; skip_whitespace(char *str)
        mov     rdx, string
        add     rdx, rax
        mov     string, rdx ; str + rax OR str[i + rax]

    .sign:
        mov     rdi, string
        call    get_sign ; get_sign(char *str)
        mov     sign, rax
        mov     rax, string 
        add     rax, rdx
        mov     string, rax
        

    xor     rcx, rcx ; int i
    mov     r8, string
    xor     r9, r9 ; res
    .mainloop:

        movzx   rdx, byte [r8 + rcx]
        test    dl, dl
        jz      .return
        
        .check_in_base:
            mov     rdi, rdx
            lea     rsi, [base_values]
            mov     rax, qword [rsi + rdi*8]
            cmp     rax, -1
            je      .return

        .add_up:
            imul    r9, base ; res *= base_len
            jo      .error
            add     r9, rax  ; res += base[i]
            jo      .error


        inc     rcx
        jmp     .mainloop

    .error:
        mov     r9, 0
        jmp     .return

    .return:
        imul    r9, sign
        mov     eax, r9d
        stack_leave
;------------------------------------------
;------------------------------------------
get_base:

    stack_enter
    stack_u64     base_values_ptr      ; size_t base_values[256]
    stack_u64     base_ptr             ; char *base                
    stack_alloc
    

    .init:
        mov         base_values_ptr, rsi
        mov         base_ptr,        rdi
        mov         r8, base_ptr
        mov         r9, base_values_ptr
        mov         r10, 0              ; int i
        mov         r11, 0              ; char c = base[i]

    .loop:
        mov     rax, base_ptr ; rax = base
        movzx   r11, byte [rax + r10] ; r11 = base[i]
        cmp     r11, 0
        je      .ret

        .test_if_num:
            mov     rdi, r11
            call    is_num
            test    rax, rax
            jnz     .test_in_base
        
        .test_if_alpha:
            mov     rdi, r11
            call    is_alpha
            test    rax, rax
            jnz     .test_in_base
            jmp     .error
        
        .test_in_base:
            mov     rax, qword [r9 + r11*8]
            cmp     rax, -1
            jne     .error 

        .assign_base_value:
            mov     qword [r9 + r11*8], r10 ; base_values[c] = i
            inc     r10
            jmp     .loop

    .ret:
        mov     rax, r10
        cmp     rax, 2
        jl      .error
        jmp     .return

    .error:
        mov     rax, -1

    .return:
        stack_leave
;------------------------------------------
;------------------------------------------
skip_whitespace:

    mov     r8, rdi   ; char *str
    xor     r9, r9    ; char c
    xor     rcx, rcx  ; int i

    .loop:

        movzx   r9, byte [r8 + rcx] ; c = string[i]
        cmp     r9, 0
        je      .return

        .test_whitespace:

            mov     rdi, r9
            call    is_whitespace
            test    rax, rax
            jz      .return
            
        inc     rcx
        jmp     .loop
       
    .return:
        mov rax, rcx
        ret
;------------------------------------------
;------------------------------------------
get_sign:

    xor     rdx, rdx

    .compare:
        movzx   eax, byte [rdi]
        cmp     al, 43
        je      .positive
        cmp     al, 45
        je      .negative
        mov     rax, 1
        jmp     .return
    
    .positive:
        mov     rax, 1
        mov     rdx, 1
        jmp     .return

    .negative:
        mov     rax, -1
        mov     rdx, 1

    .return:
        ret
;------------------------------------------
;------------------------------------------
is_whitespace:

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
        jmp     .return

    .yes:
        mov     rax, 1
    .return:
        ret
;------------------------------------------
;------------------------------------------
is_num:

    xor     rax, rax

    .check:
        cmp     rdi, 48 ; '0'
        jl      .return
        cmp     rdi, 57 ; '9'
        jg      .return
        mov     rax, 1

    .return:
        ret
;------------------------------------------
;------------------------------------------
is_alpha:

    xor     rax, rax
    
    .test_low_alpha:
        cmp     rdi, 97 ; 'a'
        jl      .test_high_alpha
        cmp     rdi, 122 ; 'z'
        jg      .test_high_alpha
        mov     rax, 1
        jmp     .return

    .test_high_alpha:

        cmp     rdi, 65 ; 'A'
        jl      .return
        cmp     rdi, 90 ; 'Z'
        jg      .return
        mov     rax, 1

    .return:
        ret
