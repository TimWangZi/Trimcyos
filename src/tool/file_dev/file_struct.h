#define TALE_SIZE 5624
#define MAX_SIZE  255
#define CS		  0x101f
#define DS		  0x202f
typedef  unsigned char      uchar;//8bit
typedef	 unsigned short int word; //16bit
typedef  unsigned long      dword;//32bit

typedef  uchar*      uchar_ptr;   //8bitָ��
typedef	 word*		 word_ptr;    //16bitָ��
typedef  dword*      dword_ptr;   //32bitָ��
#pragma pack (2)
struct FileSystemHead {
	dword tag = (dword)("tag ");  //���Ϊ��ʼ
	dword whole_table_size;		  //��������������ͷ���Ĵ�С
	word  Element_size;			  //�����������Ĵ�С
};
struct FileSystemUnit {
	word  tag = 0xf0f0;			  //��ʼ���
	word  state = CS;			  //�������ڴ����,Ĭ��cs
	word  file_type;			  //�ļ�����
	dword name = (dword)("null"); //�ļ���
	dword address_cs;			  //cs����ƫ�Ƶ�ַ
	dword address_ds;			  //ds���ص�ַ����ϵͳ������
	dword file_size;			  //�ļ���С
};
struct FileSystemTable{
	FileSystemHead hd;			  //ͷ
	dword          Table_size;	  //������������
	FileSystemUnit fu[MAX_SIZE];  //�ļ�����
};
