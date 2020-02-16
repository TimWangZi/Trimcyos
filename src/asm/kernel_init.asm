;========================
;Author:Tim Wang
;This file for init kernel
;2020/2/1/20:02
;========================
;================
;The Data area
;from 0x34c00~0xa0000
;offset
;0~100h 	VBE Info
;100~114h 	VBE CRTC Information Block
;115h~11eh  The video mode without VBE
;11fh		Video mode(FFh is vbe,00h is vga)
;120h		The GDT table
;================
org 0x7e00
SVGA_640_480 equ 111h
VGA_640_480  equ 13h
kernel_init:
	check_video_mode_64k:
		mov bx,34c0h
		mov es,bx
		mov di,0000h
		mov ax,4f01h
		mov cx,SVGA_640_480
		int 10h								;获得VBE版本信息
		call clear_mem
		
		cmp ax,004fh						;检查版本
		jne unspport
		cmp BYTE[es:di+19h],16
		jne unspport
		cmp BYTE[es:di+1bh],4
		mov ax,[es:di+0x00]
		and ax,0x0080
		jz unspport
		
		mov ax,4f02h
		mov bx,SVGA_640_480
		mov di,100h							;SVGA信息块地址
		int 10h								;启用SVGA模式
		mov bx,115h
		mov BYTE[es:bx+09h],0xff			;SVGA模式	
		jmp end_check
		unspport:
			mov bx,34c0h
			mov es,bx
			mov bx,115h
			mov ah,00h
			mov al,VGA_640_480
			int 10h
			
			mov WORD[es:bx+00h],640			;屏宽
			mov WORD[es:bx+02h],480			;屏高
			mov DWORD[es:bx+04h],0xa0000	;缓冲区地址
			mov BYTE[es:bx+08h],8			;色深
			mov BYTE[es:bx+09h],00h			;VGA模式
	end_check:
		xor ax,ax
		mov bx,ax
		mov cx,bx
		mov dx,cx
		mov es,bx
		mov di,ax
;================================
;GDT table
;name		type	address			privilege
;sys_code	code	0x7c00~0x34c00		ring0
;sys_data	data	0x34c00~0xfffff		ring0
;sys_stack	data	0x100000~0x1f0000	ring0
;usr_data	data	0x1f0000~0x41f0000	ring3
;usr_code	code	0x41f0000~0x51f0000	ring3
;usr_stack	data	0x51f0000~0x81f0000	ring3
;video_buf	data	0x????~0x????(600k)	ring0
;================================
	write_gdt:
		push ds
		mov bx,34d2h
		mov ds,bx
		mov bx,0000h
		;#0号描述符
		;空
		mov dword[bx+00h],0x00
		mov dword[bx+04h],0x00
		;#1系统代码段描述符(sys_code)
		;	基址：0x7c00
		;	段限长：0x2D000
		;	单位：byte
		;	32bit
		;	属性：可执行
		;	在内存中存在
		;	ring 0
		mov dword[bx+08h],0x7c00_D000
		mov dword[bx+0ch],0x0042_9a00
		;#2系统数据段描述符(sys_data)
		;	基址：0x34c00
		;	段限长：0xcb3ff
		;	单位：byte
		;	32bit
		;	属性：可读可写
		;	在内存中存在
		;	ring 0
		mov dword[bx+10h],0x4c00_b3ff
		mov dword[bx+14h],0x004c_9234
		;#3系统堆栈段描述符(sys_stack)
		;	基址：0x1f0000
		;	段限长：0xf0000
		;	单位：4kb
		;	32bit
		;	属性：可读可写向下拓展
		;	在内存中存在
		;	ring 0
		mov dword[bx+18h],0x0000_00f0
		mov dword[bx+1ch],0x00c0_961f
		;#4用户数据段描述符(usr_data)
		;	基址：0x1f0000
		;	段限长：0x10000
		;	单位：4kb
		;	32bit
		;	属性：可读可写向下拓展
		;	在内存中存在
		;	ring 3
		mov dword[bx+20h],0x0000_0000
		mov dword[bx+24h],0x00c1_f21f
		;#4用户数据段描述符(usr_data)
		;	基址：0x1f0000
		;	段限长：0x10000
		;	单位：4kb
		;	32bit
		;	属性：可读可写向下拓展
		;	在内存中存在
		;	ring 3
	clear_mem:
		push ax
		push bx
		push cx
		push dx
		push es
		push di
		mov bx,34d0h
		mov es,bx
		mov bx,0
		_loop:
			mov DWORD[es:bx],0000_0000h
			add bx,4
			cmp bx,256
			jle _loop
		pop di
		pop es
		pop dx
		pop cx
		pop bx
		pop ax
		ret