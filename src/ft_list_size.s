%include "../inc/libasm.inc"

section .text
    global ft_list_size


ft_list_size:

    xor     rax, rax                        ; int i = 0;

    .null_check:
        test    rdi, rdi                    ; if (!begin_list)
        jz      .return                     ; return ;
        mov     rcx, rdi

    .loop:

        .check_null:
            test    rcx, rcx                ; if (!head)
            jz      .return                 ; return ;

        mov     rcx, [rcx + S_INFO.next]    ; head = head->next

        inc     rax                         ; i++;
        jmp     .loop

    .return:
        ret

