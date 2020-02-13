/*
*=========================
*Author:Tim Wang
*File:kernel_base_asm_func.h
*This file are statement
*The function of assembly
*2020/2/11/21:45
*=========================
*/
extern void _memory_write(unsigned long address,unsigned short int data16bit);						   //向目标写入两个字节
extern unsigned long _memory_read(unsigned long address);					  						   //从目标读取两个字节

extern void _cpu_hlt(void);																			   //CPU休眠函数
extern void _select_ds(unsigned long selecter);														   //修改ds段选择子
extern void _select_ss(unsigned long selecter);														   //修改ss段选择子

extern void _system_output_8(unsigned short int address, unsigned short int data8bit);				   //端口输出函数
extern unsigned long _system_input_8(unsigned short int address);									   //端口读入函数
extern void _system_output_16(unsigned short int address, unsigned short int data16bit);			   //端口输出(16bit)函数
extern unsigned long _system_input_8(unsigned short int address);									   //端口输入(16bit)函数
