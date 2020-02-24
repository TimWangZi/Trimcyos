#define TALE_SIZE 5624
#define MAX_SIZE  255
#define CS		  0x101f
#define DS		  0x202f
typedef  unsigned char      uchar;//8bit
typedef	 unsigned short int word; //16bit
typedef  unsigned long      dword;//32bit

typedef  uchar*      uchar_ptr;   //8bit指针
typedef	 word*		 word_ptr;    //16bit指针
typedef  dword*      dword_ptr;   //32bit指针
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
