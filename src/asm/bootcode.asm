;========================
;Author:Tim Wang
;This file is boot code
;running in MBR
;2020/2/14/8:39
;Address:
;0x7E00~0x15400 系统内核加载地址
;========================
cylinder equ 2
head equ 1
sector equ 18
org 0x7c00					  ;程序开始部分
mov sp,0x7c00
mov ax,0
mov bx,ax
mov cx,bx
mov dx,cx
start:
	mov ah,00h				  ;重置软盘
	mov dl,00h				  ;驱动器A
	int 13h
	cmp ah,00h
	jne error_1
	je read_floopy

read_floopy:
	mov ax,0201h
	mov bx,07e0h
	mov es,bx
	mov bx,0
	mov cx,0002h
	mov dx,0000h
	jmp retry
	loop_1:							;for(l=0;l<3+1;l++)
		loop_2:						;for(h=0;h<1+1;h++)
			loop_3:					;for(s=1;s<18+1;s++)
				retry:				;读取错误重试
					mov al,01h
					mov ah,02h
					int 13h
					cmp ah,00h
					jne retry
				add bx,0x200
				add cl,1
				cmp cl,sector+1
				jl loop_3
			
			add dh,1
			mov cl,1
			cmp dh,head+1
			jl loop_2
		
	mov dh,0
	mov cl,1
	add ch,1
	cmp ch,cylinder+1
	jl loop_1
	jmp end_mbr
error_1:
	mov ax,0
	mov es,ax
	mov ax, msg
	mov bp, ax                    ; ES:BP表示显示字符串的地址
	mov cx, msgLen                ; CX存字符长度
	mov ax, 1301h                 ; AH=13h表示向TTY显示字符，AL=01h表示显示方式（字符串是否包含显示属性，01h表示不包含）
	mov bx, 000fh                 ; BH=00h表示页号，BL=0fh表示颜色
	mov dl, 0                     ; 列
	int 10h
hlts:
	hlt
	jmp hlts

end_mbr:
	mov ax,0
	mov bx,ax
	mov cx,bx
	mov dx,cx
	jmp 7e00h
msg:db"Can't read disk"
msgLen equ $-msg
times 510 - ($ - $$) db 0     ;填充剩余部分
dw 0aa55h 