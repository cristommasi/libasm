%include "../inc/libasm_bonus.inc"

%define begin_list rbx
%define func       r12
%define prev       r13
%define cur        r14
%define next       r15
%define disordered r9

section .text
    global ft_list_sort


ft_list_sort:

    stack_enter
    push    begin_list
    push    func
    push    prev
    push    cur
    push    next
    push    disordered

    .null_check:
        test    rdi, rdi                                                    ; if (!begin_list)
        jz      .return                                                     ; return ;
        mov     rax, [rdi]                                                  ; 
        test    rax, rax                                                    ; if (!*begin_list)
        jz      .return                                                     ; return ;
        test    rsi, rsi                                                    ; if (!(*cmp)())
        jz      .return                                                     ; return ;

    mov     begin_list, rdi                                                 ; begin_list        
    mov     func, rsi                                                       ; func = (*cmp)();
    .loop:

        mov     disordered, 0                                               ; disordered = 0
        mov     prev, 0                                                     ; prev = NULL
        mov     cur, [begin_list]                                           ; cur = *begin_list

        .inner_loop:
            test    cur, cur                                                ; if (!cur)
            jz      .test_disorder                                          ; return ;
            cmp    qword [cur + S_INFO.next], 0                             ; if (!cur->next)
            je      .test_disorder                                          ; return ;
            

            mov     next, [cur + S_INFO.next]                               ; next = cur->next;
            .compare:

                param_call func, [cur + S_INFO.data], [next + S_INFO.data]  ; int ret = cmp(cur->data, next->data);
                test    rax, rax                                            ; if (!ret)
                jz      .no_swap                                            ; goto noswap;

                .swap:

                    test    prev, prev                                      ; if (!prev)
                    jz      .update_head                                    ; goto update_head;

                    .update_prev:
                        mov     [prev + S_INFO.next], next                  ; prev->next = next
                        jmp     .continue_swap                              ; goto continue_swap;

                    .update_head:
                        mov     [begin_list], next                          ; *begin_list = next;

                    .continue_swap:
                        mov     rax, [next + S_INFO.next]                   ; temp = next->next;
                        mov     [cur + S_INFO.next], rax                    ; cur->next = temp;
                        mov     [next + S_INFO.next], cur                   ; next->next = cur;
                        mov     disordered, 1                               ; disordered = 1;
                        mov     prev, next                                  ; prev = next;
                        jmp     .increment                                  ; goto increment;

                .no_swap:
                    mov     prev, cur                                       ; prev = cur;
           
            .increment:
                mov     cur, [prev + S_INFO.next]                           ; cur = prev->next;
                jmp     .inner_loop                                         ; goto inner_loop;

        .test_disorder:                  
            test    disordered, disordered                                  ; if (disordered)
            jnz     .loop                                                   ; goto loop;


    .return:
        pop    disordered
        pop    next
        pop    cur
        pop    prev
        pop    func
        pop    begin_list
        stack_leave