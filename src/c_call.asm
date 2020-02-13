;==========================
;Author:Tim Wang
;File:cpp_call.asm
;This file are define the 
;function of cpp file
;2020/2/11/11:17
;==========================
[bits 32]
;调用时栈中的数据
;--------H
;|#3|dl |
;|#2|ebx|
;|#1|ds |<-top
;--------L
global _memory_write
global _memory_read

global _cpu_hlt
global _select_ds
global _select_ss

global _system_output_8
global _system_input_8
global _system_output_16
global _system_input_16
;#函数 _memory_write
;参数：
;	#1段选择子	16bit有效
;	#2地址		32bit有效
;	#3数据		16bit有效
;返回值:[VOID]	
;作用：写内存2字节
_memory_write:
	add esp,4
	pop ebx
	pop ecx
	pop edx
	mov ax,ds
	mov ds,bx
	mov WORD[ecx],dx
	mov ds,ax
	sub esp,16
	ret
;#函数 _memory_read
;参数：
;	#1段选择子	16bit有效
;	#2地址		32bit有效
;返回值:[DWORD](16bit有效)	
;作用：读内存2字节
_memory_read:
	add esp,4
	pop ebx
	pop ecx
	xor eax,eax
	mov dx,ds
	mov ds,bx
	mov ax,WORD[ecx]
	mov ds,dx
	sub esp,12
	ret
;#函数 _select_ds
;参数：
;	#1段选择子	16bit有效
;返回值:[VOID]	
;作用：切换数据段选择子
_select_ds:
	add esp,4
	pop ebx
	mov ds,bx
	sub esp,8
	ret
;#函数 _select_ss
;参数：
;	#1段选择子	16bit有效
;返回值:[VOID]	
;作用：切换堆栈段选择子
_select_ss:
	add esp,4
	pop ebx
	mov ss,bx
	sub esp,8
	ret
;#函数 _cpu_hlt
;参数:[VOID]
;返回值:[VOID]	
;作用:停机（在没有设置中断向量表时调用这个会导致CPU停机）
_cpu_hlt:
	hlt
	ret
;#函数 _system_output_8
;参数:
;	#1目标地址(16bit有效)
;	#2数据(16bit)(8bit有效)
;返回值:[VOID]
;作用：向指定端口输出一个字节
_system_output_8:
	add esp,4
	pop edx
	pop eax
	out dx,al
	sub esp,12
	ret
;#函数 _system_input_8
;参数:
;	#1目标地址(16bit有效)
;返回值:[DWORD(32bit)(8bit有效)]
;作用：从指定端口读入一个字节（存放在EAX中）
_system_input_8:
	add esp,4
	pop edx
	xor eax,eax
	in al,dx
	sub esp,8
	ret
;#函数 _system_output_16
;参数:
;	#1目标地址(16bit有效)
;	#2数据(16bit有效)
;返回值:[VOID]
;作用：向指定端口输出两个字节
_system_output_16:
	add esp,4
	pop edx
	pop eax
	out dx,ax
	sub esp,12
	ret
;#函数 _system_input_16
;参数:
;	#1目标地址(16bit有效)
;返回值:[DWORD(32bit)(16bit有效)]
;作用：从指定端口读入两个字节（存放在EAX中）
_system_input_16:
	add esp,4
	pop edx
	xor eax,eax
	in ax,dx
	sub esp,8
	ret
