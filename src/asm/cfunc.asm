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
global read_cs
global io_write_8
global io_read_8
global io_write_16
global io_read_16
global system_hlt

;函数memory_write
;	#1目标地址(32bit)
;	#2数据(16bit)
;	返回值：无
;	作用：向目标地址写入2个字节的数据
memory_write:
	add esp,4
	pop eax
	pop ebx
	mov WORD[ds:eax],bx
	sub esp,12
	ret
;函数memory_read
;	#1目标地址(32bit)
;	返回值：目标地址指向的数据(16bit)
;	作用：从目标地址读入2个字节的数据
memory_read:
	add esp,4
	pop ebx
	xor eax,eax
	mov ax,[ds:ebx]
	sub esp,8
	ret
;函数read_cs
;	#1目标地址(32bit)
;	返回值：目标地址指向的数据(16bit)
;	作用：读取目标地址2个字节的数据（代码段）
read_cs:
	add esp,4
	pop ebx
	xor eax,eax
	mov ax,[cs:ebx]
	sub esp,8
	ret

;函数io_write_8
;	#1目标io地址(16bit)
;	#2写入目标的数据(8bit)
;	返回值：无
;	作用：向目标端口写入1个字节的数据
io_write_8:
	add esp,4
	pop edx
	pop eax
	out dx,al
	sub esp,12
	ret
;函数io_read_8
;	#1目标io地址(16bit)
;	返回值：从目标地址读取的数据(8bit)
;	作用：从目标端口读入1个字节的数据
io_read_8:
	add esp,4
	pop edx
	xor eax,eax
	in al,dx
	sub esp,8
	ret
;函数io_write_16
;	#1目标io地址(16bit)
;	#2写入目标的数据(16bit)
;	返回值：无
;	作用：向目标端口写入2个字节的数据
io_write_16:
	add esp,4
	pop edx
	pop eax
	out dx,ax
	sub esp,12
	ret
;函数io_read_16
;	#1目标io地址(16bit)
;	返回值：从目标地址读取的数据(16bit)
;	作用：从目标端口读入2个字节的数据
io_read_16:
	add esp,4
	pop edx
	xor eax,eax
	in ax,dx
	sub esp,8
	ret
;函数system_hlt
;	#NONE
;	返回值：无
;	作用：系统停机直到中断发生
system_hlt:
	hlt
	ret

