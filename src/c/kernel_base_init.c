#include "kernel_base_asm_func.h"
void sys_init_video();
void sys_init_file();
void _start(void) {
	sys_init_video();					//视频初始化
	sys_init_file();					//文件系统初始化
	system_hlt();
}
#include "kernel_base_init_VideoInit.h"
#include "kernel_base_init_file.h"
#include "kernel_graphics.h"
