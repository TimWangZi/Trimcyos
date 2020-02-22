#include "kernel_base_asm_func.h"
#include "kernel_base_init_VideoInit.h"
void _start(void) {
	sys_init_video();					//初始化系统视频
	system_hlt();
}
