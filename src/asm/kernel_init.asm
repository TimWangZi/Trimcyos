;========================
;Author:Tim Wang
;This file for init kernel
;2020/2/1/20:02
;========================
;================
;The Data area
;from 0x15400~0xa0000
;offset
;0~100h 	VBE Info
;100~114h 	VBE CRTC Information Block
;115h~11eh  The video mode without VBE
;11fh		Video mode(FFh is vbe,00h is vga)
;120h		The GDT
;================
org 0x7e00
DATA_AREA    equ 0x1540
SVGA_640_480 equ 111h
VGA_640_480  equ 13h
kernel_init:
	check_video_mode_64k:
		mov bx,1540h
		mov es,bx
		mov di,0000h
		mov ax,4f01h
		mov cx,SVGA_640_480
		int 10h								;获得VBE版本信息
		
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
		mov bx,1540h
		mov es,bx
		mov bx,115h
		mov BYTE[es:bx+09h],0xff			;SVGA模式	
		jmp end_check
		unspport:
			mov bx,1540h
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
		
		mov bx,1552
		mov ds,bx
		mov bx,0000h
;================================
;GDT table
;name		type	address			privilege
;sys_code	code	0x7c00~0x15400		ring0
;sys_data	data	0x15400~0xfffff		ring0
;sys_stuck	data	0x100000~0x1f0000	ring0
;usr_data	data	0x1f0000~
;================================
		
		