%include "../inc/libasm.inc"

section .text
    global ft_list_push_front
    extern malloc

ft_list_push_front:

    stack_enter
    stack_u64   begin_list
    stack_u64   data
    stack_alloc


    mov     begin_list, rdi
    mov     data, rsi

    .alloc:
        mov     rdi, 16             
        call    malloc wrt ..plt
        test    rax, rax
        jz     .return
    
    .assign:
        mov     rdi, begin_list
        mov     rsi, data
        mov     rcx, [rdi]
        mov     [rax + S_INFO.data], rsi
        mov     [rax + S_INFO.next], rcx
        mov     [rdi], rax


    .return:
        stack_leave