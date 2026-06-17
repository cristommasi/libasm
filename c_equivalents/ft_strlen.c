
#include "libasm.h"

size_t      ft_strlen(const char *s) {

    size_t  i = 0;

    while (1) {

        if ((*s + i) == 0)
            break ;
        i++;
    }
    return (i);
}