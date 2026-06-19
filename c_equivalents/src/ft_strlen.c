
#include "../inc/libasm.h"

/*const char *s = rdi*/
void    ft_strlen() {

    rax ^= rax;
    
    loop:

        if ( *(char*)(rdi + rax) == 0)
            goto break_;
        rax++;
        goto loop;

    break_:
        return ;
}