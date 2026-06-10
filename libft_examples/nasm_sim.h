#ifndef NASM_SIM_H
# define NASM_SIM_H

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>



typedef struct s_stack {

	ssize_t		value;
	struct s_stack	*next;

} t_stack;

static t_stack 		*stack;

static ssize_t 	rax = 0;
static ssize_t 	rcx = 0;
static ssize_t	rdx = 0;
static ssize_t 	rsi = 0;
static ssize_t 	rdi = 0;
static ssize_t	r8  = 0;
static ssize_t	r9  = 0;
static ssize_t	r10 = 0;
static ssize_t	r11 = 0;

static ssize_t  flags = 0;

typedef void (*t_func)(void);

// pop stack
static void     pop(ssize_t *reg)
{
    if (!stack)
        return ;
    t_stack *tmp    = stack;
    *reg			= stack->value;
    stack      		= stack->next;
    free(tmp);
}

//stack
static void    push(ssize_t *reg)
{
    t_stack *node = malloc(sizeof(t_stack));
    if (!node)
        return ;
    node->value = *reg;
    node->next  = stack;
    stack  = node;
}

static void    call(t_func f) {

    f();
}

static void    ret(void) {

    return ;
}

// mov rax, rdi
static void	mov_reg(ssize_t *dest, ssize_t *src) {

    *dest = *src;
}

// mov rax, 5
static void    mov_imm(ssize_t *dest, ssize_t val) { 
    *dest = val; 
}

// mov r10b, BYTE [rdi + rax]
static void    mov_mem(ssize_t *dest, char *addr) { 
    *dest = *addr; 
}

// mov BYTE [rdi + rax], r10b
static void    mov_to_mem(char *addr, ssize_t *src) { 
    *addr = (char)*src; 
}

static void    xor(ssize_t *dest, ssize_t *src) {

    *dest ^= *src;
}

static void    and(ssize_t *dest, ssize_t *src) {

    *dest &= *src;
}

static void    or(ssize_t *dest, ssize_t *src) {

    *dest |= *src;
}

static void    add(ssize_t *dest, ssize_t value) {

    *dest += value;
}

static void    sub(ssize_t *dest, ssize_t value) {

    *dest -= value;
}

static void    inc(ssize_t *reg) {

    (*reg)++;
}

static void    dec(ssize_t *reg) {

    (*reg)--;
}

static void    not(ssize_t *reg) {

    ~(*reg);
}

static void    neg(ssize_t *reg) {

    (*reg) = -(*reg);
}

static void    mul(ssize_t *dest, ssize_t *src) {

    *dest *= *src;
}

static void    mul3(ssize_t *rega, ssize_t *regb, ssize_t *dest) {

    *dest = (*rega) * (*regb);
}



static void    cmp(ssize_t a, ssize_t b) { 

    flags = a - b; 
}

static void    test(ssize_t a, ssize_t b)  { 

    flags = a & b; 
}

static void    xor_flags(ssize_t a)        { 

    flags = a ^ a; 
} 


static int     je(void)    { 

    return (flags == 0); 
}        

static int     jne(void)   {
    
    return (flags != 0); 
} 

static int     jz(void)    {
    
    return (flags == 0); 
} 


static int     jnz(void)   {
    
    return (flags != 0); 
}

static int     js(void)    {
    
    return (flags < 0); 
}

static int     jns(void)   {
    
    return (flags >= 0); 
}

static int     jl(void)    {
    
    return (flags < 0); 
}
static int     jle(void)   {
    
    return (flags <= 0); 
}
static int     jg(void)    {
    
    return (flags > 0); 
}

static int     jge(void)   {
    
    return (flags >= 0); 
}

static int     jb(void)    {
    
    return ((size_t)flags < 0); 
}

static int     jbe(void)   {
    
    return ((size_t)flags <= 0); 
}

static int     ja(void)    {
    
    return ((size_t)flags > 0); 
}

static int     jae(void)   {
    
    return ((size_t)flags >= 0); 
}


#endif