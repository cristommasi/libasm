
%include "../inc/libasm.inc"

section .text
	global  ft_strdup
    extern  malloc
    extern  ft_strlen
    extern  ft_strcpy


ft_strdup:

    stack_enter
    stack_u64     param0
    stack_u64     len
    stack_u64     temp
    stack_alloc

    mov     param0, rdi
    mov     len, 0
    mov     temp, 0

    .len:
        xor     rax, rax            
        call    ft_strlen wrt ..plt 
        mov     len, rax            

    .alloc:
        xor     rax, rax            
        mov     rdi, len            
        inc     rdi                 
        call    malloc wrt ..plt    
        test    rax, rax            
        jz     .error               
        mov     temp, rax           

    .copy:
        mov     rdi, temp           
        mov     rsi, param0         
        call    ft_strcpy wrt ..plt 
        jmp     .return


    .error:

        mov  rax, 0

    .return:
        stack_leave
