#include <stddef.h>

char *_ft_strcpy(char *dest, char *src) {

    char i = 0;
    while (1) {

        char temp = *(src + i);
        *(dest + i) = temp;

        if ( *(src + i) == 0) {
            
            return (dest);
        }
        i++;
    }
    return (NULL);
}