
#include "libasm.h"

/*const char *s = rdi*/
void    ft_strdup() {

    rax ^= rax;
    push(rbp, "push(rbp)");
    rsp -= 8;// char    *param0;
    rsp -= 8;// ssize_t len;
    rsp -= 8;// char    *temp;
    
    
    

    *(ssize_t *)(stack + rbp - 0)  = rdi;

    *(ssize_t *)(stack + rbp - 8) = 0;

    *(ssize_t *)(stack + rbp - 16) = 0;


    
    //len:
        rax ^= rax;
        ft_strlen();
        *(ssize_t *)(stack + rbp - 8) = rax;

   // alloc:
        rax ^= rax;
        rdi = *(ssize_t *)(stack + rbp - 8);
        rdi++;
        rax = (ssize_t)malloc(rdi);
        if ( rax == 0 )
            goto error;
        *(ssize_t *)(stack + rbp - 16) = rax;

    
    //copy:
        rdi = *(ssize_t *)(stack + rbp - 16);
        rsi = *(ssize_t *)(stack + rbp - 0);
        ft_strcpy();
        
        goto return_;

    
    error:
        rax = 0;

    return_:
        rbp = pop();
        return ;


}