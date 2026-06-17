
%include "../inc/libasm_bonus.inc"

%define begin_list  rbx
%define f_cmp       r12
%define f_free_fct  r13
%define cur         r14
%define prev        r15


section .text
    global ft_list_remove_if
    extern free

ft_list_remove_if:

    stack_enter
    stack_u64   data_ref
    stack_alloc
    push        begin_list
    push        f_cmp
    push        f_free_fct
    push        cur
    push        prev
    sub         rsp, 8

    .null_check:
        test    rdi, rdi
        jz      .return
        test    rsi, rsi
        jz      .return
        test    rdx, rdx
        jz      .return
        test    rcx, rcx
        jz      .return
    
    .init:
        mov     begin_list, rdi
        mov     data_ref, rsi
        mov     f_cmp, rdx
        mov     f_free_fct, rcx
        mov     cur, [begin_list]
        mov     prev, 0
        
    .loop:

        test    cur, cur                                ; if (cur == NULL)
        jz      .return                                 ; return ;

        .compare:
            mov     rdi, [cur + S_INFO.data]
            mov     rsi, data_ref
            call    f_cmp                               ;int ret =  cmp(cur->data, data_ref)
            test    rax, rax                            ; if (ret != 0)
            jnz      .continue                          ; goto continue;

            .remove_node:

                mov     rdi, qword [cur + S_INFO.data]        
                call    f_free_fct                      ; free_fct(cur->data)
                mov     rax, [cur + S_INFO.next]        ; cur->next

                test    prev, prev                      ; if (!prev)
                jz     .update_head                     ; goto update_head;

                .update_prev:
                    mov     [prev + S_INFO.next], rax   ; prev->next = cur->next;
                    jmp     .continue_swap              ; goto continue_swap;

                .update_head:
                    mov     [begin_list], rax           ; *begin_list = cur->next

                .continue_swap:
                    mov     rdi, cur
                    push    rax
                    call    free wrt ..plt              ; free(node)
                    pop     rax
                    mov     cur, rax                    ; cur = cur->next
                    jmp     .loop                       ; goto loop;

        .continue:                                      ; elseif (ret == 0)
            mov     prev, cur                           ; prev = cur;
            mov     cur, [cur + S_INFO.next]            ; cur = cur->next;
            jmp     .loop                               ; goto loop;


    .return:
        add     rsp, 8
        pop     prev
        pop     cur
        pop     f_free_fct
        pop     f_cmp
        pop     begin_list
        stack_leave
   