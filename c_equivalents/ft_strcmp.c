#include "libasm.h"


int     ft_strcmp(const char *s1, const char *s2) {

    int     i = 0;
    char temp1;
    char temp2;

    while (1) {

        temp1 = *(s1 + i);
        temp2 = *(s2 + i);
        if (temp1 != temp2)
            break ;
        if (temp1 == 0)
            break ;
        i++;
    }
    int res = (int)temp1;
    int res2 = (int)temp2;
    res -= res2;
    return (res);
}