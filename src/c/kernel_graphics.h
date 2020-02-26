void video_write_16(word x,word y,word pixel){
    word_ptr wp = (word_ptr)(video_option.liner_video_buffer + (video_option.wide * x + video_option.hight * y) * 2);
    *wp = pixel;
}
void video_write_8(word x,word y,uchar pixel){
    uchar_ptr cp = (uchar_ptr)(video_option.bank_video_buffer + video_option.wide * x + video_option.hight * y);
    *cp = pixel;
}
