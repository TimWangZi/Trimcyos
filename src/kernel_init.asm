;========================
;Author:Tim Wang
;This file for init kernel
;2020/2/1/20:46
;========================
;org 0x7c00
org 0x8ff0
kernel_init:
	mov ax,VGA_CARD_TYPE
	cmp ax,SUPER_VGA
	je init_super_vga_card
	jne init_vga_card
	
	init_super_vga_card:
		mov	ax,9000h				;check vbe
		mov es,ax
		mov dl,0
		mov ax,4f00h
		int 10h
		cmp ax,004fh
		jne init_vga_card
		mov cx,0106h
		mov ax,0x4f01
		int 10h
		cmp ax,004fh
		jne init_vga_card
		
		mov ax,4f02h				;超级VGA显示卡
		mov bx,0106h				;1280*1024 256色
		int 10h
		mov ax,1280
		mov bx,1024
		mov [cs:SCREAWIDE],ax
		mov [cs:SCREAHIGH],bx
		mov DWORD[VRAM_ADDRESS],0xe0000000
		
		jmp end_init_vga
	init_vga_card:
		mov ax,0013h				;640*480 256色
		int 10h
		mov ax,640
		mov bx,480
		mov [cs:SCREAWIDE],ax
		mov [cs:SCREAHIGH],bx
		mov DWORD[VRAM_ADDRESS],0x000a0000
		jmp end_init_vga
		
end_init_vga:
;这中间应该要加一个PIC初始化
;后面再加吧
	init_gdt:
		mov ax,ds
		push ax
		mov ax,GDT_BASE/16
		mov ds,ax 
		mov dx,0000h
		mov bx,0
		;GDT第一个描述符是空的
		mov dword[bx+0x00],0x00
		mov dword[bx+0x04],0x00
		;#下面是代码段描述符
		;	段基地址：0x00008ff0
		;	段长度：12KB
		;	类型：可执行
		;	特权：RING0
		;	在内存中存在
		;	单位:4kb
		mov dword[bx+0x08],0x8ff0_0003
		mov dword[bx+0x0c],0x00c09800
		;#下面是显示缓冲区描述符(VGA)
		;	段基地址：0x000a0000
		;	段长度：300KB
		;	类型：可读可写可向上拓展
		;	特权：RING0
		;	在内存中存在
		;	单位：4kb
		mov dword[bx+0x10],0x0000_0075
		mov dword[bx+0x14],0x00c0_920a
		;#下面是堆栈段描述符
		;	段基地址:0x001f0000
		;	段长度:512kb
		;	类型：可读可写可向下拓展
		;	特权:RING0
		;	内存中存在
		;	单位：4kb
		mov dword[bx+0x18],0x0000_0080
		mov dword[bx+0x1c],0x00c0_961f
		;#下面是数据段描述符
		;	段基地址:0x00280000
		;	段长度:512kb
		;	类型：可读可写可向下拓展
		;	特权:RING0
		;	内存中存在
		;	单位：4kb
		mov dword[bx+0x20],0x0000_0080
		mov dword[bx+0x24],0x00C0_9228
		
		pop ax
		mov ds,ax
		mov WORD[cs:GDT_SZIE],31
	_32bit_protect_mode:
		;加载GDT
		lgdt [cs:GDTR_DATA]
		;打开A20桥
		mov al,00000010b;设第一位(从第零位开始)为1
		out 0x92,al     ;从0x92端口打开A20桥
		cli				;关中断
		;进入保护模式
		mov eax,cr0
		or eax,1
		mov cr0,eax 		;CR0设第一位为1
							;重置CS段寄存器
		jmp dword 0x0008:(clear_pipe-0x00008ff0)
		[bits 32]
		clear_pipe:			;设置堆栈段，数据段
			mov ecx,0x20
			mov ds,ecx
			mov ecx,0x0018
			mov ss,ecx
			mov esp,0x001f0000-1 ;设置栈顶
			mov ebp,0x170000   ;设置EBP
			mov eax,0xfff
			
			mov eax,0		;清空寄存器
			mov ebx,eax
			mov ecx,ebx
			mov edx,ecx
			jmp dword 0x0008:0x200
SUPER_VGA equ 002fh    
VGA_CARD equ  003fh
VGA_CARD_TYPE equ VGA_CARD
VRAM_ADDRESS equ  0X7FFF
SCREAWIDE: resb 2
SCREAHIGH: resb 2
GDT_BASE equ 0xf000
GDT_SZIE dw 0000h
GDTR_DATA:
dw 0xffff			;GDT限长
dd 0x0000_f000		;GDT基址
times 510 - ($ - $$) db 0 
dw 0000h