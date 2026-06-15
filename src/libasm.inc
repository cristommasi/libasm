%ifndef LIBASM_INC
%define LIBASM_INC

%assign _var_offset 0

%define _align8(x) (((x) + 7) / 8) * 8

;--------------------------------------------------------------------------------------------------DEC-VARS

%macro stack_enter 0 
    push rbp
    mov  rbp, rsp
    %assign _var_offset 0
%endmacro

%macro stack_alloc 0
    %assign _padded ((_var_offset + 15) / 16) * 16
    sub  rsp, _padded
%endmacro

%macro stack_leave 0
    mov  rsp, rbp
    pop  rbp
    ret
%endmacro

;--------------------------------------------------------------------------------------------------DEC-VARS
; Declare vars of %1=name, 
%macro stack_u64 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 qword [rbp - _%1_off]
%endmacro

%macro stack_u32 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 dword [rbp - _%1_off]
%endmacro

%macro stack_u16 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 word [rbp - _%1_off]
%endmacro

%macro stack_u8 1
    %assign _var_offset _var_offset + 8
    %assign _%1_off _var_offset
    %define %1 byte [rbp - _%1_off]
%endmacro

;--------------------------------------------------------------------------------------------------DEC-VARS
;--------------------------------------------------------------------------------------------------ARRAYS
; Declare an array of %1=name, %2=count
%macro stack_arr_u64 2
    %assign _arr_bytes _align8(%2 * 8)
    %assign _var_offset _var_offset + _arr_bytes
    %assign _%1_off _var_offset
    %define %1 rbp - _%1_off
%endmacro

%macro stack_arr_u32 2
    %assign _arr_bytes _align8(%2 * 4)
    %assign _var_offset _var_offset + _arr_bytes
    %assign _%1_off _var_offset
    %define %1 rbp - _%1_off
%endmacro

%macro stack_arr_u16 2
    %assign _arr_bytes _align8(%2 * 2)
    %assign _var_offset _var_offset + _arr_bytes
    %assign _%1_off _var_offset
    %define %1 rbp - _%1_off
%endmacro

%macro stack_arr_u8 2
    %assign _arr_bytes _align8(%2 * 1)
    %assign _var_offset _var_offset + _arr_bytes
    %assign _%1_off _var_offset
    %define %1 rbp - _%1_off
%endmacro

;--------------------------------------------------------------------------------------------------ARRAYS

%define S_INFO.data 0
%define S_INFO.next 8



%endif