;========================
;Author:Tim Wang
;This file for init kernel
;2020/2/1/20:02
;========================
;================
;The Data area
;from 0x34c00~0x134bff
;offset
;0~100h 	VBE CRTC Information Block
;115h~11eh  The video mode without VBE
;11fh		Video mode(FFh is vbe,00h is vga)
;120h		The temporary GDT table
;500h+		Mainsys
;================
org 0x7e00
SVGA_640_480 equ 111h
VGA_640_480  equ 13h
kernel_init:
	check_video_mode_64k:
		mov bx,34c0h
		mov es,bx
		mov di,0000h
		mov ax,4f00h
		int 10h								;获得VBE版本信息
		
		cmp ax,004fh
		jne unspport
		cmp word[es:di+4],0x0200			;检查版本
		jb unspport
		
		mov ax,4f01h
		mov cx,SVGA_640_480
		int 10h								
		
		cmp ax,004fh						
		jne unspport
		cmp BYTE[es:di+19h],16
		jne unspport
		cmp BYTE[es:di+1bh],4
		mov ax,[es:di+0x00]
		and ax,0x0080
		jz unspport
		
		mov ax,4f02h
		mov bx,SVGA_640_480 + 0x4000
		mov di,000h							;SVGA信息块地址
		int 10h								;启用SVGA模式（覆盖原版本信息）,+0x4000表示启用高地址线性缓冲区
		call clear_mem						;清空信息块后1024字节
		mov bx,11fh
		mov BYTE[es:bx],0xff				;SVGA模式	
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
			mov BYTE[es:bx+0ah],00h			;VGA模式
	end_check:
		xor ax,ax
		mov bx,ax
		mov cx,bx
		mov dx,cx
		mov es,bx
		mov di,ax
		call write_temporary_gdt
		jmp _32bit_protect_mode
;================================
;Main GDT table
;name		type	address			privilege
;sys_stack	data	0x0x7c00~0x5ff		ring0
;sys_code	code	0x7c00~0x34c00		ring0
;sys_data	data	0x34c00~0xffffffff	ring0
;usr_data	data	0x1f0000~0x41f0000	ring3-|
;usr_code	code	0x41f0000~0x51f0000	ring3 |-data
;usr_stack	data	0x51f0000~0x81f0000	ring3 |
;video_buf	data	0x????~0x????(600k)	ring0-|
;================================
;先加载临时描述符
;然后将用户代码拷贝到目标地址
;最后加载主GDT描述符
	write_temporary_gdt:	;临时GDT分区表
		push ds
		mov bx,34d2h
		mov ds,bx
		mov bx,0000h
		;#0号描述符
		;空
		mov dword[bx+00h],0x00
		mov dword[bx+04h],0x00
		;#1系统堆栈描述符(sys_stack)
		;	基址：0x0600
		;	段限长：0x7600
		;	属性：可读可写
		;	32bit
		;	单位：byte
		mov dword[bx+08h],0x0600_7600
		mov dword[bx+0ch],0x0040_9200
		;#2系统代码描述符(sys_code)
		;	基址：0x7c00
		;	段限长：0x2c
		;	属性：可读可执行
		;	32bit
		;	单位：4kb
		mov dword[bx+10h],0x7c00_002c
		mov dword[bx+14h],0x00c0_9a00
		;#3系统数据描述符(sys_data)
		;	基址：0x34c00
		;	段限长：0xfffff
		;	属性：可读可写
		;	32bit
		;	单位：4kb
		mov dword[bx+18h],0x4c00_ffff
		mov dword[bx+1ch],0x00cf_9203
		pop ds
		mov word[_length],20h
		mov dword[_base],0x0003_4d20
		ret
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
			cmp bx,1024
			jle _loop
		pop di
		pop es
		pop dx
		pop cx
		pop bx
		pop ax
		ret
	_32bit_protect_mode:
		lgdt [GDTR0_DATA]
		
		in al,0x92              ;南桥芯片内的端口
		or al,0000_0010B
		out 0x92,al             ;打开A20:第21根地址线
		
		cli 					;关中断
		
		mov eax,cr0
		and eax,0x7fffffff		;禁用分页
		or eax,1
		mov cr0,eax             ;设置PE位，置为1，进入保护模式
		
		jmp 0x0010:(flush-0x7c00)
		[bits 32]
		flush:
			mov ax,0x0008
			mov ss,ax
			mov ax,0x0018
			mov ds,ax
			xor eax,eax
			mov esp,75ffh
			mov ebp,esp
			
			xor eax,eax
			mov ebx,0xffff
			;STI					;允许中断发生....个屁！
			jmp 0x0010:0x0000_0400
			
GDTR0_DATA:
_length:DW 0x0000 
_base:DD 0x0000_00000
times 512 - ($ - $$) db 0