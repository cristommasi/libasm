#include "libasm.h"

/*const char *s1, const char *s2*/
void    ft_strcmp() {

    rax ^= rax;

    loop:
        r8 = *(unsigned char*)(rdi + rax);
        r9 = *(unsigned char*)(rsi + rax);

        if ( r8 != r9 )
            goto break_;

        if ( r8 == 0 )
            goto break_;

        rax++;
        goto loop;

    break_:
        rax = r8;
        r10 = r9;
        rax -= r10;
        return ;
}