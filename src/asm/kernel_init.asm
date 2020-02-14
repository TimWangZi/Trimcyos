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
;???~???The video mode without VBE
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
		mov bx,SVGA_640_480
		mov di,100h
		int 10h
		jmp end_check
		unspport:
			
	end_check