;========================
;Author:Tim Wang
;This file is boot code
;running in MBR
;2020/1/28/20:46
;Address:
;0x8ff0~0xB3F0 系统内核加载地址
;========================
org 0x7c00					  ;程序开始部分
check_disk:				  	  ;磁盘调用号0，重置磁盘
	mov ah,0x00
	int 13h
	cmp ah,0h
	jne disk_error
	je  load_disk_2t18
load_disk_2t18:				  ;从2扇区，0柱面，0磁头开始读，数据读到0x8ff0后的18x512字节的空间中
	mov ax,0x08ff
	mov es,ax
	mov bx,0x0000
	mov ax,0
	
	mov ah,02h
	mov al,1
	mov ch,0
	mov cl,2
	mov dh,0
	mov dl,0
	jmp read
	load_loop_1:
		add cl,1
		read:				  ;缺陷设计
		int 13h
		add bx,0x0200
		;mov ah,01h			  ;for debug
		cmp ah,00h
		jne disk_error		  ;错误处理
		mov ah,02h
		cmp cl,18
		jne load_loop_1		  ;循环至18号磁道
		je end_mbr			  ;mbr结束

disk_error:
	push ax
	mov ax,0
	mov es,ax
	mov dh,0
	pop ax
	
	cmp ah,01h
	je err1
	cmp ah,02h
	je err2
	cmp ah,03h
	je err3
	cmp ah,04h
	je err4
	cmp ah,05h
	je err5
	cmp ah,06h
	je err6
	cmp ah,80h
	je err7
	jmp erro
	err1:;错误一
		mov ax, error_string_1
		mov bp, ax                    ; ES:BP表示显示字符串的地址
		mov cx, error_string_1_l      ; CX存字符长度
		mov ax, 1301h                 ; AH=13h表示向TTY显示字符，AL=01h表示显示方式（字符串是否包含显示属性，01h表示不包含）
		mov bx, 000fh                 ; BH=00h表示页号，BL=0fh表示颜色
		int 10h
		loops:
			hlt
			jmp loops
	
	err2:;错误二
		mov ax, error_string_2
		mov bp, ax                    
		mov cx, error_string_2_l      
		mov ax, 1301h                 
		mov bx, 000fh                 
		int 10h
		loops2:
			hlt
			jmp loops2
	
	err3:;错误三
		mov ax, error_string_3
		mov bp, ax                    
		mov cx, error_string_3_l      
		mov ax, 1301h                 
		mov bx, 000fh                 
		int 10h
		loops3:
			hlt
			jmp loops3
			
	
	err4:;错误四
		mov ax, error_string_4
		mov bp, ax                    
		mov cx, error_string_4_l      
		mov ax, 1301h                 
		mov bx, 000fh                 
		int 10h
		loops4:
			hlt
			jmp loops4
	
	err5:;错误五
		mov ax, error_string_5
		mov bp, ax                    
		mov cx, error_string_5_l      
		mov ax, 1301h                 
		mov bx, 000fh                 
		int 10h
		loops5:
			hlt
			jmp loops5
			
	err6:;错误六
		mov ax, error_string_6
		mov bp, ax                    
		mov cx, error_string_6_l      
		mov ax, 1301h                 
		mov bx, 000fh                 
		int 10h
		loops6:
			hlt
			jmp loops6
			
	err7:;超时错误
		mov ax, error_string_7
		mov bp, ax                    
		mov cx, error_string_7_l      
		mov ax, 1301h                 
		mov bx, 000fh                 
		int 10h
		loops7:
			hlt
			jmp loops7
			

	erro:;其他错误
		mov ax, error_string_o
		mov bp, ax                    
		mov cx, error_string_o_l      
		mov ax, 1301h                 
		mov bx, 000fh                 
		int 10h
		loopso:
			hlt
			jmp loopso
end_mbr:					  ;清空寄存器
	mov ax,0
	mov bx,ax
	mov cx,bx
	mov dx,bx
	jmp 0x8ff0

error_string_1: db 'Undefine command!'
error_string_1_l: equ $-error_string_1

error_string_2: db 'Target address not found!'
error_string_2_l: equ $-error_string_2

error_string_3: db 'Disk write protection!'
error_string_3_l: equ $-error_string_3

error_string_4: db 'Sector not found!'
error_string_4_l: equ $-error_string_4

error_string_5: db 'Reset failed!'
error_string_5_l: equ $-error_string_5

error_string_6: db 'Remove the floppy disk!'
error_string_6_l: equ $-error_string_6

error_string_7: db 'Read timeout!'
error_string_7_l: equ $-error_string_7

error_string_o: db 'Undefine error!'
error_string_o_l: equ $-error_string_o
times 510 - ($ - $$) db 0     ;填充剩余部分
dw 0aa55h 