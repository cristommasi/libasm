#ifndef LIBASM_H
#define LIBASM_H

#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

static ssize_t rax = 0;
static ssize_t rcx = 0;
static ssize_t rdx = 0;
static ssize_t rdx = 0;
static void  *rdi = 0;
static void  *rsi = 0;

int     ft_strcmp(const char *s1, const char *s2);

#endif