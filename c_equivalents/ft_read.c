
#include "libasm.h"

ssize_t     ft_read(int fd, const void *buf, size_t count) {

    ssize_t res = syscall(SYS_read, rdi, buf, count);

    if (res < 0) {

        res = -res;
        int *errno_ = __errno_location();
        *errno_ = (int)res;
        res = -1;
    }
    return (res);
}