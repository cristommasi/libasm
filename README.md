# libasm

A small Assembly library written in NASM, together with C implementations that try to mimic what the Assembly code is doing internally.

## NASM Macros

As part of the project, I also created my own NASM macros to make working with the stack and local variables easier.

Instead of manually calculating stack offsets for every local variable, the macros keep track of the current stack offset and let me declare variables like:

```nasm
stack_enter
stack_u64     param0
stack_u64     len
stack_u64     temp
stack_alloc
```

This handles creating the stack frame, keeping track of variable offsets, allocating the required stack space, and restoring the stack when the function returns.

I also added macros for different integer sizes and arrays:

```nasm
stack_u64
stack_u32
stack_u16
stack_u8

stack_arr_u64
stack_arr_u32
stack_arr_u16
stack_arr_u8
```

For example, the NASM implementation of `ft_strdup` uses these macros to make the function look closer to how you would normally structure it in C:

```nasm
ft_strdup:

    stack_enter
    stack_u64     param0
    stack_u64     len
    stack_u64     temp
    stack_alloc

    mov     param0, rdi
    mov     len, 0
    mov     temp, 0

    .len:
        xor     rax, rax
        call    ft_strlen wrt ..plt
        mov     len, rax

    .alloc:
        xor     rax, rax
        mov     rdi, len
        inc     rdi
        call    malloc wrt ..plt
        test    rax, rax
        jz      .error
        mov     temp, rax

    .copy:
        mov     rdi, temp
        mov     rsi, param0
        call    ft_strcpy wrt ..plt
        jmp     .return

    .error:
        mov     rax, 0

    .return:
        stack_leave
```

The goal was to make stack management less repetitive while still having a clear idea of where each variable lives relative to `rbp`.

## C equivalents

The C side of the project takes this idea in the opposite direction.

This somewhat chaotic-looking C code is my attempt to mimic what the Assembly version is doing internally.

I created global 64-bit variables to represent the x86-64 registers:

```c
rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8 ... r15
```

I also implemented a manual stack using an array of `unsigned char`, with `push()` and `pop()` functions.

For example, the C implementation of `ft_strdup()` follows the same general structure as its NASM equivalent:

```c
rax ^= rax;
push(rbp);
rbp = rsp;
rsp -= 24;

*(ssize_t *)(stack + rbp - 8) = rdi;
*(ssize_t *)(stack + rbp - 16) = -1;
*(ssize_t *)(stack + rbp - 24) = -1;
```

Instead of letting the compiler manage registers, the stack, and local variables, I am explicitly doing it myself.

The idea was to experiment with what happens underneath normal C code and get a better understanding of things like:

* x86-64 registers
* Stack frames
* `rsp` and `rbp`
* Function arguments
* Return values
* Local variables
* `push` / `pop`
* Memory allocation
* Calling conventions

The result is definitely more complicated than normal C, but that's kind of the point. It is an attempt to recreate, at a higher level, some of the work that the compiler and CPU normally handle for us.

The repository contains both the NASM implementations and their C equivalents, making it possible to compare how the same functions are represented at different levels.
