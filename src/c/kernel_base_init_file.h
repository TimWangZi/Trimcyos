#define TALE_SIZE 5624
#define MAX_SIZE  255
#define CS		  0x101f
#define DS		  0x202f
#define TYPE_FILE 0x0001		//文件类型：文件
#define TYPE_APP  0x0002		//文件类型：应用程序
#pragma pack (2)
struct FileSystemHead {
	dword tag = (dword)("tag ");  //标记为开始
	dword whole_table_size;		  //整个描述表（包括头）的大小
	word  Element_size;			  //单个描述符的大小
};
struct FileSystemUnit {
	word  tag = 0xf0f0;			  //开始标记
	word  state = CS;			  //本体所在代码段,默认cs
	word  file_type;			  //文件类型
	dword name = (dword)("null"); //文件名
	dword address_cs;			  //cs段中偏移地址
	dword address_ds;			  //ds加载地址（由系统决定）
	dword file_size;			  //文件大小
};
struct FileSystemTable{
	FileSystemHead hd;			  //头
	dword          Table_size;	  //描述符的数量
	FileSystemUnit fu[MAX_SIZE];  //文件表体
};
FileSystemTable file_sys_head;
void sys_init_file(){
	for(int i = 0;i < sizeof(file_sys_head);i++){
        memory_write(i + &file_sys_head,read_cs(i + 0x400));			//复制文件数据到结构体
    }
	if(file_sys_head.hd.tag != (dword)("tag ") ||						//如果出错就关机
	file_sys_head.fu[0].tag != 0xf0f0
	){						//出错就关机
		io_write_16(0x1004, 0x2001);
		system_hlt();
	}
	return;
}
