#ifndef _COMMAND_H_
#define _COMMAND_H_

//#include "main.h"
#include "builtin.h"

#define MAX_COMMAND_SIZE (1024)

// fork() 来执行命令
int execute_shell_command(COMMAND *cmd);

#endif