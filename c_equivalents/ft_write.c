
#include "libasm.h"

ssize_t     ft_write(int fd, const void *buf, size_t count) {

    ssize_t res = syscall(SYS_write, fd, buf, count);

    if (res < 0) {

        res = -res;
        int *errno_ = __errno_location();
        *errno_ = (int)res;
        res = -1;
    }
    return (res);
}