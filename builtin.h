#ifndef BUILTIN
#define BUILTIN

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <readline/rlstdc.h>
#include <readline/keymaps.h>
#include <readline/tilde.h>
#include <readline/chardefs.h>
#include <readline/rlconf.h>
#include <readline/rltypedefs.h>

#include "config.h"

typedef struct {
  char *name;			/* User printable name of the function. */
  rl_icpfunc_t *func;		/* Function to call to do the job. */
  char *doc;			/* Documentation for this function.  */
} COMMAND;

extern COMMAND commands[];

int my_help(char*);
int my_list(char*);
int my_quit(char*);
int my_rename(char*);
int my_stat(char*);
char* my_pwd (void);
int my_cd(char*array);
int my_touch(char*array);
int my_histary(char*array);
int my_mkdir(char*array);
int my_alias(char*array);
int my_fg(char*array);
int my_bg(char*array);
int my_jobs(char*array);
int my_touch(char*name);
int my_echo(char*array);
int my_cp(char*des, char*src);
int my_mv(char*des, char*src);
int my_rm(char*name);
int my_mkdir(char*name);




#define pwd() my_pwd()
#define cd() my_cd()
#define touch() my_touch()
#define histary() my_histary()


//数解析array中的路径名，将其存放在pathname中。
char* path_analysis(char*array,char*pathname);

//该函数解析命令行
//char* cmdline_analysis(char*array,);


bool cmd_line_fun_search(void);

COMMAND *find_command (char *name);

//char *stripwhite (char *s);//去除字符串两端的空格、Tab

#endif