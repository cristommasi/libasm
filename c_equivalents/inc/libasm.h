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

static inline void print_stack(const char *instr)
{
	ssize_t	i;
	ssize_t	addr;
	ssize_t	value;
	ssize_t	start;


	start = rbp;
    printf("--------------------------------------------- | %s\n", instr);
	for (i = 0; i < 12; i++)
	{
		addr = start - (i * 8);

		if (addr < 0 || addr >= STACK_SIZE)
			continue ;

		value = *(ssize_t *)(stack + addr);

        printf( "stack[0x%05zx] | %#018zx", (size_t)addr & 0xFFFF, (size_t)value);

		if (addr == rsp && addr == rbp)
			printf(" | rsp-rbp");
		else if (addr == rsp)
			printf(" | rsp    ");
		else if (addr == rbp)
			printf(" | rbp    ");
        else
            printf(" |        ");

        printf(" | \n");

	}
    printf("\n");
}


static inline void    push(ssize_t value)
{
    rsp -= 8;
    *(ssize_t *)(stack + rsp) = value;

}
 
static inline ssize_t     pop(void)
{
    ssize_t value;

    value = *(ssize_t *)(stack + rsp);
    rsp += 8;

    return (value);
}

static inline void    stack_init(void)
{
    rsp = STACK_SIZE;
    rbp = STACK_SIZE;
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