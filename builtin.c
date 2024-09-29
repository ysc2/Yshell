#include "builtin.h"

COMMAND commands[] = {
  { "help", my_help, "Display this text" },
  { "cd", my_cd, "Change to directory DIR" },
  { "?", my_help, "Synonym for `help'" },
  { "list", my_list, "List files in DIR" },
  { "ls", my_list, "Synonym for `list'" },
  { "pwd", my_pwd, "Print the current working directory" },
  { "quit", my_quit, "Quit using Fileman" },
  { "rename", my_rename, "Rename FILE to NEWNAME" },
  { "stat", my_stat, "Print out statistics on FILE" },
  { "bg", my_bg, "Command to put a process in background" },
  { "fg", my_fg, "Command to bring a process to foreground" },
  { (char *)NULL, (Function *)NULL, (char *)NULL }
};


bool cmd_line_fun_search(void){
    FILE* fd = fopen("~/Yshell/cmd_fun.txt","r");
    char array[128] = {'0'};
    if(fread(array,1,sizeof(array),fd) != 128){
        fprintf(stderr,"fread函数发生了错误");
        exit(1);
    }
    
}
char* cmdline_analysis(char*array){


}


char* path_analysis(char* src,char* pathname){
    if(realpath(src,pathname) == NULL){
        fprintf(stderr,"readpath函数发生了错误");
        exit(-1);
    }
    return pathname;
}


char* my_pwd(void){
    return (getcwd(path_name,MAX_PATH_NAME));
}


int my_cd (char*array){
    if(chdir(array) == -1){
        perror("chdir函数发生了错误");
        return 1;
    }

}

int my_help(char*)
{
    for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
        printf("%s：%s\n",commands[i].name,commands[i].doc);
    }

    return 0;
}


COMMAND *find_command (char *name)
{
    register int i;

    for (i = 0; commands[i].name; i++)
        if (strcmp (name, commands[i].name) == 0)
        return (&commands[i]);

    return ((COMMAND *)NULL);
}

int my_fg(char*array)
{

}

int my_bg(char*array)
{

}