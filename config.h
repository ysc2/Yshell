#ifndef CONFIG
#define CONFIG

//#include "main.h"

#define SEPARATOR '@' //配置分隔符

#define CMD_ARRAY_I 0//cmd_array数组从0开始
#define NAME_LINE 0 //定义用户名、主机名第一次打印的列位置
#define NAME_ROW 11 //定义用户名、主机名第一次打印的行位置
#define MAX_USR_NAME 128 //定义用户名数组的最大字符数
#define MAX_HOST_NAME 30 //定义主机名数组的最大字符数
#define MAX_PATH_NAME 128//定义最长路径名
#define MAX_CMD_ARRAY 1024//定义存储命令行的数组的长度

static char usr_name [MAX_USR_NAME];
static char host_name [MAX_HOST_NAME];
static char path_name [MAX_PATH_NAME];
static char* cmd_array [MAX_CMD_ARRAY];

#endif