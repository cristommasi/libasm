#ifndef LIBASM_HPP
#define LIBASM_HPP

#include <unistd.h>
#include <sys/syscall.h> 
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

extern ssize_t rax;
extern ssize_t rbx;
extern ssize_t rcx;
extern ssize_t rdx;
extern ssize_t rsi;
extern ssize_t rdi;
extern ssize_t rbp;
extern ssize_t rsp;
extern ssize_t r8; 
extern ssize_t r9;
extern ssize_t r10;
extern ssize_t r11;
extern ssize_t r12;
extern ssize_t r13;
extern ssize_t r14;
extern ssize_t r15;


#define STACK_SIZE 65536

extern unsigned char stack[STACK_SIZE];

static inline void print_stack(char *ptr, char *str, ssize_t value, char *command) {


    if (str)
        printf("stack[%p] = %s - %s\n",  ptr, str, command);
    else
        printf("stack[%p] = %zu - %s\n",  ptr, value, command);

}
 
static inline void    push(ssize_t value, char *command)
{
    rsp -= 8;
    *(ssize_t *)(stack + rsp) = value;
    rbp = rsp;

}
 
static inline ssize_t     pop(void)
{
    rsp = rbp;
    ssize_t value = *(ssize_t *)(stack + rsp);
    rsp += 8;


    return value;
}



/*int fd = rdi, const void *buf = rsi, size_t count = rcx*/
void    ft_write();
/*const char *s = rdi*/
void    ft_strlen();
/*char *dest = rdi, char *src == rsi*/
void    ft_strcpy();
/*const char *s1, const char *s2*/
void    ft_strcmp();
/*int fd = rdi, const void *buf = rsi, size_t count = rcx*/
void    ft_read();
/*const char *s = rdi*/
void    ft_strdup();




#endif