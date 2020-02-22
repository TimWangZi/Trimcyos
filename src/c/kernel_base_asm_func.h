/*
*=========================
*Author:Tim Wang
*File:kernel_base_asm_func.h
*This file are statement
*The function of assembly
*2020/2/18/14:25
*=========================
*/
typedef  unsigned char      uchar;//8bit
typedef	 unsigned short int word; //16bit
typedef  unsigned long      dword;//32bit

typedef  uchar*      uchar_ptr;//8bit指针
typedef	 word*		 word_ptr; //16bit指针
typedef  dword*      dword_ptr;//32bit指针


extern void memory_write(dword _address, word _data);	//写内存
extern word memory_read(dword _address);				//读内存
extern word read_cs(dword _address);					//读代码段

extern void  io_write_8(word _address, uchar _data);	//写端口(1字节)
extern uchar io_read_8(word _address);					//读端口(1字节)
extern void  io_write_16(word _address, word _data);	//写端口(2字节)
extern word  io_read_16(word _address);					//读端口(2字节)

extern void  system_hlt(void);							//CPU停机，直到中断
