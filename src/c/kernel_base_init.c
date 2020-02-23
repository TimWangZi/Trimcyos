#include "kernel_base_asm_func.h"
void sys_init_video();
void _start(void) {
	sys_init_video();					//视频初始化
	system_hlt();
}
#include "kernel_base_init_VideoInit.h"