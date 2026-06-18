#include "libasm.h"


/*char *dest = rdi, char *src == rsi*/
void    ft_strcpy() {

    rax ^= rax;

    loop:

        r8 = *(char*)(rsi + rax);
        *(char*)(rdi + rax) = r8;
        
        if ( r8 == 0 )
            goto break_;
        rax++;
        goto loop;

    break_:
        rax = rdi;
        return ;

}