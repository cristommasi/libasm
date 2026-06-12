%ifndef LIBASM_INC
%define LIBASM_INC

%assign _var_offset 0

%define _align8(x) (((x) + 7) / 8) * 8

;--------------------------------------------------------------------------------------------------DEC-VARS

%macro STACK_ENTER 0 
    push rbp
    mov  rbp, rsp
    %assign _var_offset 0
%endmacro

%macro STACK_LEAVE 0
    mov  rsp, rbp
    pop  rbp
    ret
%endmacro

%macro STACK_ALLOC 0
    sub  rsp, _var_offset
%endmacro

;--------------------------------------------------------------------------------------------------DEC-VARS
; Declare vars of %1=name, 
%macro var_u64 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 qword [rbp - _%1_off]
%endmacro

%macro var_u32 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 dword [rbp - _%1_off]
%endmacro

%macro var_u16 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 word [rbp - _%1_off]
%endmacro

%macro var_u8 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 byte [rbp - _%1_off]
%endmacro

%macro var_ptr 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 qword [rbp - _%1_off]
%endmacro


;--------------------------------------------------------------------------------------------------DEC-VARS



;--------------------------------------------------------------------------------------------------SET-VALUES
; Set value of of %1=name, %2=value/reg
%macro mov_u64 2
    mov  rax, %2
    mov  %1,  rax
%endmacro

%macro mov_u32 2
    mov  %1, %2
%endmacro

%macro mov_u16 2
    mov  %1, %2
%endmacro

%macro mov_u8 2
    mov  %1, %2
%endmacro

%macro mov_ptr 2
    lea  rax, [rel %2]
    mov  %1,  rax
%endmacro
;--------------------------------------------------------------------------------------------------SET-VALUES

;--------------------------------------------------------------------------------------------------ARRAYS
; Declare an array of %1=name, %2=count
%macro arr_u64 2
    %assign _arr_bytes _align8(%2 * 8)
    %assign _var_offset _var_offset + _arr_bytes
    %assign _%1_off _var_offset
    %define %1 rbp - _%1_off
%endmacro

%macro arr_u32 2
    %assign _arr_bytes _align8(%2 * 4)
    %assign _var_offset _var_offset + _arr_bytes
    %assign _%1_off _var_offset
    %define %1 rbp - _%1_off
%endmacro

%macro arr_u16 2
    %assign _arr_bytes _align8(%2 * 2)
    %assign _var_offset _var_offset + _arr_bytes
    %assign _%1_off _var_offset
    %define %1 rbp - _%1_off
%endmacro

%macro arr_u8 2
    %assign _arr_bytes _align8(%2 * 1)
    %assign _var_offset _var_offset + _arr_bytes
    %assign _%1_off _var_offset
    %define %1 rbp - _%1_off
%endmacro

;--------------------------------------------------------------------------------------------------ARRAYS




%endif