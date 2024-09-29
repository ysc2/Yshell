#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <readline/rlstdc.h>
#include <readline/keymaps.h>
#include <readline/tilde.h>
#include <readline/chardefs.h>
#include <readline/rlconf.h>
#include <readline/rltypedefs.h>


#include "job.h"    
#include "command.h"
#include "builtin.h"
#include "log.h"

char* Yshell_logo[] = {
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

const char *reset = "\033[0m";  // 重置颜色
const char *red = "\033[31m";   // 红色
const char *green = "\033[32m"; // 绿色
const char *yellow = "\033[33m"; // 黄色
const char *blue = "\033[34m";  // 蓝色
const char *purple = "\033[35m"; // 紫色
const char *cyan = "\033[36m";  // 青色
const char *white = "\033[37m"; // 白色


#define HISTORY_LOG         "/tmp/Yshell_Debug.log"
#define NAME_USER           "Yshell: "

//这里是命令的状态
enum shell_command_status {NO_COMMAND, RUNNING, STOPPED};

typedef struct Yshell_job_node {
    Yshell_job job;
    struct Yshell_job_node *next;
}Yshell_job_node;


typedef struct Yshell_job_list{
    
    Yshell_job_node *head, *tail;      /* list of jobs suspended or running */
    
    int count_jobs;                     /* number of such jobs */

} Yshell_job_list;


/* Yshell Control Block                                                 */
typedef struct Yshell_control_block{
    
    Yshell_job fg_job;                /* currently executing foreground job */
    
    double execution_time;              /* execution time of last command */
    
    char history_commands_file[128];    /* command history log file */
    
    Yshell_job_list jobs;              /* list of currently suspened and runing jobs */
    
    char pwd[128];                      /* previous working directory */

} Yshell_control_block;


Yshell_control_block ysh_cb;
//初始化整个shell
int init_ysh();

//打印logo
void print_ysh_logo();

//执行命令
void execute_cmd(char *cmd);

//查找命令
int find_cmd(char *cmd);

//解析命令
int parse_cmd(char *cmd);

//初始化shell控制块
void init_control_block(Yshell_control_block *cb);


//获取输入命令
char *get_cmd();

int execute_line(char *line);
#endif