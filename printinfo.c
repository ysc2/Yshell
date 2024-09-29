#include "printinfo.h"
#include "init.h"
#include "config.h"


void get_info_name(void){

    uid_t userid;
    struct passwd* pwd;
    userid=getuid();
    if((pwd=getpwuid(userid)) == NULL){
        fprintf(stderr,"getpwuid函数发生了错误\n");
        exit (1);
    }

    strncpy(usr_name,pwd->pw_name,MAX_USR_NAME);

    if(gethostname(host_name,MAX_HOST_NAME) < 0){
        fprintf(stderr,"gethostname函数发生了错误\n");
        exit(1);
    }
}


void print_info_name(WINDOW* frist,size_t a,size_t b){

    get_info_name();
    mvprintw(a,b,"%s%c%s:",usr_name,SEPARATOR,host_name);
    wrefresh(frist);
}