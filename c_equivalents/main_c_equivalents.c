#include "libasm.h"


unsigned char stack[STACK_SIZE] = {0};
ssize_t rax = 0, rbx = 0, rcx = 0, rdx = 0, rsi = 0, rdi = 0, rbp = 0, 
rsp = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;

static void    stack_init(void)
{
    rsp = STACK_SIZE;
    rbp = STACK_SIZE;
}

int     main(void) {

    stack_init();

    char *s1 = strdup("Hello\n");
    char *s2 = strdup("World\n");
    char *s3 = "Hola mundo\n";
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) return (1);
    char buffer[128];


    write(1, "ft_write = ", 11);
    rdi = 1;rsi = (ssize_t)s1;rcx = 6;
    ft_write();


    rdi = fd;rsi = (ssize_t)buffer;rcx = 11;
    ft_read();
    printf("ft_read = %zu = %s\n", rax, buffer);
    close(fd);


    rdi = (ssize_t)s1;
    ft_strlen();
    printf("ft_strlen = %zu\n", (size_t)rax);


    rdi = (ssize_t)s1; rsi = (ssize_t)s2;
    ft_strcmp();
    printf("ft_strcmp = %d\n", (int)rax);


    rdi = (ssize_t)s1; rsi = (ssize_t)s2;
    ft_strcpy();
    printf("ft_strcpy = %s", (char*)rax);

    rdi = (ssize_t)s3;
    ft_strdup();
    char *res = (char*)rax;
    printf("ft_strdup = %s", (char*)res);

    

    
    return 0;
}