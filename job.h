#ifndef _JOB_H
#define _JOB_H


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include "command.h"
#include "log.h"

#define MAX_PROCESS_NAME_SIZE (128)




//该结构体是 Yshell jobs 进程结构体
typedef struct Yshell_job_process{
    
    char process_name[MAX_PROCESS_NAME_SIZE];       /* 进程名称 */

    pid_t pid;                                      /* 与命令相关的进程 pid */

    struct Yshell_job_process *next;               /* 列表中的下一个元素 */

}Yshell_job_process;


//该结构体是 Yshell jobs 结构体，使用列表来进行组织
typedef struct Yshell_job {
    
    Yshell_job_process *head, *tail;   /* 队列头和尾 */
    
    char command[MAX_COMMAND_SIZE];     /* 实际的命令名称 */

    int command_status;                 /* 命令的状态 */

    int process_count;                  /* 单个命令创建的进程数 */

}Yshell_job;




//初始化job链表
void init_job_list(Yshell_job_list *jl);
//添加job到链表
void add_job_to_list(Yshell_job_list *jl, Yshell_job job);
//删除job从链表
void remove_job_from_list(Yshell_job_list *jl, Yshell_job job);
//打印job链表
void print_job_list(Yshell_job jl, int index);
//销毁job链表
void destroy_job_list(Yshell_job_list *jl);
//恢复job到前台
void resume_jobs_fg(Yshell_job_list *jl, Yshell_job *job, int index);
//恢复job到后台
void resume_jobs_bg(Yshell_job_list *jl, int index);

//
void resume_job(Yshell_job *jl, int index);

//遍历job链表
void traverse_job(Yshell_job job);

void destroy_job(Yshell_job* job);

void kill_job(Yshell_job *job);

void suspend_job(Yshell_job *job);
#endif // _JOB_H