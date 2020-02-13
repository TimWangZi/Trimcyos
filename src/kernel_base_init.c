#include "kernel_base_asm_func.h"
void _start(void){
	//_system_output_16(0x1004,0x2001);
	unsigned long ds1=0x00080000,ds2=0x00200000;
	_select_ds(&ds1);
	for(int i=0;i<640*480;i++){
		_memory_write(i,0x0f0f);
	}
	_select_ds(&ds2);
	_cpu_hlt();
}
