
#include "../inc/libasm.h"

/*int fd = rdi, const void *buf = rsi, size_t count = rcx*/
void    ft_read() {

    rax = SYS_read;
    rax = syscall(rax, rdi, rsi, rcx);
    if (rax < 0)
        goto error;

    return ;

    error:

        rax = -rax;
        rbx = rax;
        rax = (ssize_t)__errno_location();
        *(int*)rax = (int)rbx;
        rax = -1;
        return ;
}