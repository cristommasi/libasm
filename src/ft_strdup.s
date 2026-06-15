
section .text
	global  ft_strdup
    extern  malloc
    extern  ft_strlen
    extern  ft_strcpy


ft_strdup:

    stackenter
    var_u64     len         ; int len;
    var_u64     temp        ; char *temp;
    var_u64     param0      ; char *param0;
    stackalloc


    set_u64     param0, rdi ; param0 = s;
    set_u64     len, 0      ; len = 0;
    set_u64     temp, 0     ; temp = NULL;

    .len:
        xor     rax, rax    ; int ret = 0;
        call    ft_strlen   ; ret = ft_strlen(src);
        mov     len, rax    ; len = ret;

    .alloc:
        xor     rax, rax    ; ret = 0;
        mov     rdi, len    ; size_t size = len;
        inc     rdi         ; size++;
        call    malloc      ; ret = malloc(size);
        test    rax, rax    ; if (!ret)
        jne     .error      ; goto error;
        mov     temp, rax   ; temp = ret;

    .copy:
        mov     rdi, temp    ; char *dest = temp;
        mov     rsi, param0  ; char *src = param0
        call    ft_strcpy    ; char *res = ft_strcpy(dest, src);
        jmp     .return


    .error:
        mov  rax, 0

    .return:
        stackleave