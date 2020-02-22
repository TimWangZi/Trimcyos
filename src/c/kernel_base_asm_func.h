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

typedef  uchar*      uchar_ptr;//8bitָ��
typedef	 word*		 word_ptr; //16bitָ��
typedef  dword*      dword_ptr;//32bitָ��


extern void memory_write(dword _address, word _data);	//д�ڴ�
extern word memory_read(dword _address);				//���ڴ�
extern word read_cs(dword _address);					//�������

extern void  io_write_8(word _address, uchar _data);	//д�˿�(1�ֽ�)
extern uchar io_read_8(word _address);					//���˿�(1�ֽ�)
extern void  io_write_16(word _address, word _data);	//д�˿�(2�ֽ�)
extern word  io_read_16(word _address);					//���˿�(2�ֽ�)

extern void  system_hlt(void);							//CPUͣ����ֱ���ж�
