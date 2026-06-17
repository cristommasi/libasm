#include "libasm.h"

char    *ft_strcpy(char *dest, char *src) {

    size_t i = 0;

    while (1) {

        char c = (*src + i);

        *(dest + i) = c;

        if ((*src + i) == 0)
            break ;
        
        i++;
    }
    return (dest);
}