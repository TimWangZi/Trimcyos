#include "kernel_base_asm_func.h"
#include "kernel_base_init_VideoInit.h"
void _start(void) {
	sys_init_video();					//��ʼ��ϵͳ��Ƶ
	system_hlt();
}
