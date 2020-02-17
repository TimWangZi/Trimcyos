;==========================
;Author:Tim Wang
;File:cfunc.asm
;This file are function  
;for c language
;Target:ELF-32 
;2020/2/17/15:59
;==========================
;C语言调用规范
;	函数func(a,b,c);
;	调用:
;		push c
;		push b
;		push a
;		call func
;	被调用:
;		pop a
;		pop b
;		pop c
;		call func
[bits 32]
global memory_write
global memory_read
global io_write_8
global io_read_8
global io_write_16
global io_read_16
global system_hlt

;函数memory_write
;	#1目标地址(32bit)
;	#2数据(8bit)
;