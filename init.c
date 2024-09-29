#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include "init.h"
#include "main.h"

void init_screen(WINDOW* frist){

    start_color();
    // if(has_colors() == FALSE){	
    //     endwin();
	// 	printf("你的终端并不支持颜色显示\n");
	// 	exit(1);
    // }
    initscr();
    char* Yshell_char[] = {
    "__     __  _          _ _ ",
    "\\ \\   / / | |        | | |",
    " \\ \\_/ /__| |__   ___| | |",
    "  \\   / __| '_ \\ / _ \\ | |",
    "   | |\\__ \\ | | |  __/ | |",
    "   |_||___/_| |_|\\___|_|_|",
       "Auther:      ysc",
       "Version:     1.0",  
       "Time:        2023.9.27",
    };
    for (int i = 0; i < 9; i++){
        printw("%s\n",Yshell_char[i]);
    }
    wrefresh(frist);
    return ;
}


void init_Yshell(WINDOW* frist){
    // scroll(frist);
    keypad(frist, TRUE);//启用特殊键值
    // scrollok(frist,1);
    //cbreak();
    init_screen(frist);
    init_control_block(&ysh_cb);
    
    return ;
}