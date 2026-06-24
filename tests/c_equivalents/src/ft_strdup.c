
#include "../inc/libasm.h"

/*const char *s = rdi*/
void    ft_strdup() {

    rax ^= rax;
    push(rbp);//print_stack("ft_strdup - push(rbp);");
    rbp = rsp;//print_stack("rbp = rsp;");
    rsp -= 24;//print_stack("rsp -= 24;");
    
    *(ssize_t *)(stack + rbp - 8)  = rdi;   // char    *param0;//print_stack("stack[rbp - 8] = rdi; ");
    *(ssize_t *)(stack + rbp - 16) = -1;     // ssize_t len;//print_stack("stack[rbp - 16] = 0;");
    *(ssize_t *)(stack + rbp - 24) = -1;     // char    *temp;//print_stack("stack[rbp - 24] = 0;");

    
    /* len: */
        rax ^= rax;
        ft_strlen();
        *(ssize_t *)(stack + rbp - 16) = rax;//print_stack("stack[rbp - 16] = rax");

   /* alloc: */
        rax ^= rax;
        rdi = *(ssize_t *)(stack + rbp - 16);//print_stack("rdi = stack[rbp - 16];");
        rdi++;
        rax = (ssize_t)malloc(rdi);
        if ( rax == 0 )
            goto error;
        *(ssize_t *)(stack + rbp - 24) = rax;//print_stack("stack[rbp - 24] = rax;");

    
    /* copy: */
        rdi = *(ssize_t *)(stack + rbp - 24);
        rsi = *(ssize_t *)(stack + rbp - 8);
        ft_strcpy();
        
        goto return_;

    
    error:
        rax = 0;

    return_:
        rsp = rbp;//print_stack("rsp = rbp;");
        rbp = pop();//print_stack("rbp = pop();");
        return ;


}


