#ifndef INIT
#define INIT

#define ctrl(x)           ((x) & 0x1f)

void get_info_name(void);//获取用户名和主机名

void init_screen(WINDOW* frist);//初始化屏幕

void init_Yshell(WINDOW* frist);//初始化整个shell

#endif