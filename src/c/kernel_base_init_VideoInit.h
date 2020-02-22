#define TAG_ADDR_VIDEO_TAG    0x11f
#define RAM_ADDR_VIDEO_BUF	  0x28
#define SCREEN_WIDE_ADDR      0x12
#define SCREEN_HIGH_ADDR	  0x14
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
	uchar_ptr tag = (uchar_ptr)(TAG_ADDR_VIDEO_TAG);		//0xFF是VBE 0x00是VGA 其他是出错
	if ((*tag) == VIDEO_MODE_VBE) {							//VBE
		video_option.mode = VIDEO_MODE_VBE;
		video_option.bank_video_buffer = NONE;
		dword_ptr liner_vb = (dword_ptr)(RAM_ADDR_VIDEO_BUF);
		video_option.liner_video_buffer = *liner_vb;
		dword_ptr scr_size = (dword_ptr)(SCREEN_WIDE_ADDR);
		video_option.wide = *scr_size;
		scr_size = (dword_ptr)(SCREEN_HIGH_ADDR);
		video_option.hight = *scr_size;
		video_option.bits_per_pixel = 16;
		return;
	}else if ((*tag) == VIDEO_MODE_VGA) {
		video_option.mode = VIDEO_MODE_VGA;
		video_option.bank_video_buffer = 0xa0000;
		video_option.wide = 640;
		video_option.hight = 480;
		video_option.bits_per_pixel = 8;
		return;
	}else {
		io_write_16(0x1004, 0x2001);
		system_hlt();
	}
}