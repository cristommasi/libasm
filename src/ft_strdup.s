
%include "src/libasm.inc"

section .text
	global  ft_strdup
    extern  malloc
    extern  ft_strlen
    extern  ft_strcpy
    extern __errno_location

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
        xor     rax, rax            ; int ret = 0;
        call    ft_strlen wrt ..plt ; ret = ft_strlen(src);
        mov     len, rax            ; int len = ret;

    .alloc:
        xor     rax, rax            ; ret = 0;
        mov     rdi, len            ; size_t size = len;
        inc     rdi                 ; size++;
        call    malloc wrt ..plt    ; ret = malloc(size);
        test    rax, rax            ; if (!ret)
        jz     .error               ; goto error;
        mov     temp, rax           ; char *temp = ret;

    .copy:
        mov     rdi, temp           ; char *dest = temp;
        mov     rsi, param0         ; char *src = saved_param
        call    ft_strcpy wrt ..plt ; char *res = ft_strcpy(dest, src);
        jmp     .return


    .error:

        mov  rax, 0

    .return:
        stack_leave
