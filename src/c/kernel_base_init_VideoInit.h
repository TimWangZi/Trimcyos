#define TAG_ADDR_VIDEO_BUFFER 0x11f
#define VIDEO_MODE_VGA		  0x00
#define VIDEO_MODE_VBE		  0xff
#define NONE				  0x0000
struct Video_option{
	uchar     mode;
	word_ptr  liner_video_buffer;
	uchar_ptr bank_video_buffer;
	word	  wide;
	word      hight;
	uchar	  bits_per_pixel;
}video_option;
void sys_init_video() {
	uchar_ptr tag = (uchar_ptr)(TAG_ADDR_VIDEO_BUFFER);		//0xFF是VBE 0x00是VGA 其他是出错
	if ((*tag) == VIDEO_MODE_VBE) {							//VBE
		video_option.mode = VIDEO_MODE_VBE;
		video_option.bank_video_buffer = NONE;
		dword_ptr dpt=(dword_ptr)(
	}
}