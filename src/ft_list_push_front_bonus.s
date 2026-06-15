%include "src/libasm.inc"

section .text
    global ft_list_push_front
    extern malloc

ft_list_push_front:

    stack_enter
    push rdi
    push rsi

    .alloc:
        mov     rdi, 16             
        call    malloc wrt ..plt
        test    rax, rax
        jz      .error
    
    .assign:
        pop     rsi
        pop     rdi
        mov     rcx, [rdi]
        mov     [rax + S_INFO.data], rsi
        mov     [rax + S_INFO.next], rcx
        mov     [rdi], rax
        ret

    .error:
        pop     rsi
        pop     rdi
        ret
        