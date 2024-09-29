#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "init.h"
//#include "printinfo.h"
#include "main.h"
//#include "emacs.h"


//int main (int argc , char** argv , char** env)
//{
    //WINDOW* frist = newwin(LINES,COLS,0,0);
    //init_Yshell(frist);
    //keypad(stdscr,TRUE);

    //int line = NAME_LINE;
    //int row = NAME_ROW;
    //int cmd_array_i = CMD_ARRAY_I;
    //char ctrl;
    //for(;;){
        //switch(getch()){
        //case 'q':
            //endwin();
            //return 0;
        //case '\n':
        //case 'KEY_ENTER':
        //if (row == LINES)
        //{
            //row = 0;
            //clear();
        //}
        //print_info_name(frist,row++,line);
        //// case ctrl('l'):
        ////     clear();
        ////     break;
        
        //// default:
        ////     break;
        //// clear();
        //// case ://快捷键CTRL+U

        //// case ://快捷键CTRL+
        //case KEY_UP://方向键向上
           ////printf("KEY_UP");
            //break;
        //case KEY_LEFT://左
            //move(row,line--);
            //break;
        //case KEY_RIGHT://右
            //printf("KEY_RIGHT");
            //break;
        //case KEY_DOWN://下
            //printf("KEY_DOWN");
            //break;
        //default:
            //getstr(cmd_array[cmd_array_i++]);
            
        //} 
//}
//}

int done;

int main(int argc, char* *argv)
{
    init_ysh();


    char *line;
    char *s;
    for ( ; done == 0; ){
        line = readline ("Yshell: ");

        if (!line)
            break;

        s = stripwhite (line);

        if (*s){
            add_history (s);
            execute_line (s);
        }

        free (line);
    }
    return 0;
    
}

void print_ysh_logo()
{
    for (int i = 0; i < 9; i++){
        printf("%s\n", Yshell_logo[i]);
    }
}

int init_ysh()
{
    print_ysh_logo();//打印logo

    initialize_readline();
    return 0;
}


char *stripwhite (char *s)
{
    for(; *s ==' ' || *s == '\t'; s++);

    if(*s == '\0')return s;

    char *p = s + strlen(s) - 1;

    for(; *p == ' ' || *p == '\t'; p--) *p = '\0';

    return s;

}

void parse_args(char *line, char **args);

//初始化控制块
void init_control_block(Yshell_control_block *ysh_cb)
{
    char cwd[512];

    /* initialize the foreground command running in shell */
    init_job(&(ysh_cb->fg_job), "");

    /* execution time of the last command */
    ysh_cb->execution_time = 0.0;
    
    /* history log file                         */
    strcpy(ysh_cb->history_commands_file, HISTORY_LOG);
    
    /* suspended or running list of jobs for the shell */
    init_job_list(&(ysh_cb->jobs));
    
    /* default previous directory is the home directory */
    getcwd(cwd, 512);//获取当前路径的绝对路径
    strcpy(ysh_cb->pwd, cwd);   char cwd[512];

    /* initialize the foreground command running in shell */
    init_job(&(ysh_cb->fg_job), "");

    /* execution time of the last command */
    ysh_cb->execution_time = 0.0;
    
    /* history log file                         */
    strcpy(ysh_cb->history_commands_file, HISTORY_LOG);
    
    /* suspended or running list of jobs for the shell */
    init_job_list(&(ysh_cb->jobs));
    
    /* default previous directory is the home directory */
    getcwd(cwd, 512);//获取当前路径的绝对路径
    strcpy(ysh_cb->pwd, cwd);

}

int execute_line (char *line)
{
    register int i;
    COMMAND *command;
    char *word;

    /* Isolate the command word. */
    i = 0;
    while (line[i] && whitespace (line[i]))
        i++;
    word = line + i;

    while (line[i] && !whitespace (line[i]))
        i++;

    if (line[i] == '&'){
        add_job_to_list();
    }
    if (line[i])
        line[i++] = '\0';

    command = find_command (word);

    if (!command)
        {
        fprintf (stderr, "%s: No such command for FileMan.\n", word);
        return (-1);
        }

    /* Get argument to command, if any. */
    while (whitespace (line[i]))
        i++;

    word = line + i;

    /* Call the function. */
    return ((*(command->func)) (word));
}

char *get_cmd()
{
    char *cmd = (char*)malloc(1024);

    readline(NAME_USER);
    add_history(cmd);

    
}