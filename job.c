#include "job.h"
#include "main.h"

//初始化job链表
void init_job_list(Yshell_job_list *jl)
{
    jl->head = jl->tail = NULL;
    jl->count_jobs = 0;
    return;
}

//添加job到链表
void add_job_to_list(Yshell_job_list *jl, Yshell_job job)
{
    Yshell_job_node *new_job_node = (Yshell_job_node *)malloc(sizeof(Yshell_job_node));
    if(new_job_node == NULL) {
        PRINT_ERR("malloc failed"); 
    }
    new_job_node->job = job;
    new_job_node->next = NULL;
    
    /* 第一个要添加到作业列表中的作业 */
    if(jl->head == NULL && jl->tail == NULL) {
        jl->head = jl->tail = new_job_node;
        jl->count_jobs++;
        return;
    }
    new_job_node->next = jl->head;
    jl->head = new_job_node;
    jl->count_jobs++;
    return;
}


//恢复job到前台
void resume_jobs_fg(Yshell_job_list *jl, Yshell_job *job, int index)
{
    if(no_jobs(*jl)) {
        PRINT_EXECPTION("no foreground jobs present"); 
        return;
    } 
    Yshell_job_node* ptr = jl->head, *temp = NULL;
    while(ptr != NULL && index > 1) {
        temp = ptr;
        ptr = ptr->next;
        index--;
    }
    if(ptr == NULL) {
        PRINT_EXECPTION("no foreground jobs for given argument");
        return;
    }

    /* job which is made to start in foreground if it was stopped
     */
    resume_job(&(ptr->job), index);
    *job = ptr->job;

    /* delete the node from the job list */
    if(temp == NULL) {
        /* deleting the first node in the list */
        jl->head = jl->head->next;
        free(ptr);
    } else {
        temp->next = ptr->next;
        free(ptr);
    }
    jl->count_jobs--;
    return;
}
//恢复job到后台
void resume_jobs_bg(Yshell_job_list *jl, int index)
{
    if(no_jobs(*jl)) {
        PRINT_EXECPTION("no background jobs present");
        return;
    }
    Yshell_job_node* ptr = jl->head;
    while(ptr != NULL && index > 1) {
        ptr = ptr->next;
        index--;
    }
    if(ptr == NULL) {
        PRINT_EXECPTION("no background jobs for given argument");
        return;
    }
    /* there is not change in the data structure */
    if(ptr->job.command_status == RUNNING) {
        PRINT_EXECPTION("process is already running in background");
        return;
    } else {
        resume_job(&(ptr->job), index);
    }
    return;
}

/* traverse the job lists : prints the list of running and suspensed jobs */
void print_jobs(Yshell_job_list jobs) {
     Yshell_job_node *ptr = jobs.head;
    if(ptr == NULL) {
        PRINT_EXECPTION("no suspeneded or stopped jobs");
        return;
    }
    int i = 1;
    while(ptr != NULL) {
        print_job(ptr->job, i++);
        ptr = ptr->next;
    }
}


/* destory all the jobs which are currently active */
void destroy_jobs(Yshell_job_list *jobs) {
    Yshell_job_node *ptr = jobs->head, *temp;
    while(ptr != NULL) {
        kill_job(&(ptr->job));
        jobs->count_jobs--;
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
    jobs->head = jobs->tail = NULL;
    return;
}


/* returns true if there are no jobs suspended or running */
bool no_jobs(Yshell_job_list jobs) {
    if(jobs.head == NULL && jobs.tail == NULL) {
        return true;
    }
    return false;
}

/* delelte the job having the given pid */
bool delete_job(Yshell_job_list *jobs, pid_t pid) {
    Yshell_job_node *ptr = jobs->head, *temp = NULL;
    int index = 1;
    while(ptr != NULL) {
        if(delete_sub_job(&(ptr->job), pid, index)) {
            /* now check if the given process is completely done
             * thus free the allocated memory to data structure 
             */
            if(ptr->job.head == NULL) {
                if(temp == NULL) {
                    jobs->head = ptr->next;
                    if(jobs->head == NULL) {
                        jobs->tail = NULL;
                    }
                } else {
                    temp->next = ptr->next; 
                }
                free(ptr);
                jobs->count_jobs--;
            } 
        }  
        temp = ptr;
        ptr = ptr->next;
        index++;
    }
    return false;
}


//删除job从链表
void remove_job_from_list(Yshell_job_list *jl, Yshell_job job)
{

    return ;
}

//销毁job链表
void destroy_job_list(Yshell_job_list *jl)
{

    return ;
}

//检查是否还有job
bool check_job(Yshell_job_list jl)
{
    if(jl.head == NULL && jl.tail == NULL) {
        return true;
    }
    return false;
}

//
void resume_job(Yshell_job *jl, int index)
{
    Yshell_job_process*ptr = jl->head;
    if(ptr == NULL) {
        PRINT_EXECPTION("job has no associated processes");
        return;
    } 
    while(ptr != NULL) {
        kill(ptr->pid, SIGCONT);
        ptr = ptr->next; 
    }
    jl->command_status = RUNNING;
    print_job_list(*jl, index);
    return;
}

void traverse_job(Yshell_job job) {
    Yshell_job_process*ptr = job.head;
    while(ptr != NULL) {
        printf("(%s, %d)\t", ptr->process_name, ptr->pid);
        ptr = ptr->next;
    }
    printf("\n");
    return;
}

/* destories the job and allocated resources */
void destroy_job(Yshell_job* job) {
    Yshell_job_process *ptr = job->head, *temp;
    while(ptr != NULL) {
        temp = ptr->next; 
        free(ptr);
        ptr = temp;
    }
    job->head = job->tail = NULL;
    job->process_count = 0;
    return;
}

/* kills the job's running process 
 * Note : this frees the dynamically allocated resources 
 */
void kill_job(Yshell_job *job) {
    Yshell_job_process *ptr = job->head;
    while(ptr != NULL) {
        kill(ptr->pid, SIGINT); 
        ptr = ptr->next;
    }
    destroy_job(job);
    return;
}

/* suspends the job's running processes 
 * Note this doesn't free the dynamically allocated resources 
 */
void suspend_job(Yshell_job *job) {
    Yshell_job_process *ptr = job->head;
    while(ptr != NULL) {
        kill(ptr->pid, SIGSTOP);
        ptr = ptr->next;
    }
    job->command_status = STOPPED;
    print_job(*job, ysh_cb.jobs.count_jobs + 1);
    return;
}

bool delete_sub_job(Yshell_job *jobs, pid_t pid, int index) {
    Yshell_job_process *ptr = jobs->head, *temp = NULL;
    while(ptr != NULL) {
        if(ptr->pid == pid) {
            /* you need to delete this particular node from the list */ 
            if(temp == NULL) {
                jobs->head = ptr->next;
                if(jobs->head == NULL) {
                    jobs->tail = NULL;
                }
            } else {
                temp->next = ptr->next;
            }
            PRINT_JOB_DONE(index, pid, ptr->process_name);
            free(ptr);
            jobs->process_count--;
            return true;
        } 
        temp = ptr;
        ptr = ptr->next;
    }
    return false;
}

//打印job链表
void print_job_list(Yshell_job jl, int index)
{
    Yshell_job_process *ptr = jl.head;
    if(ptr == NULL) {
        PRINT_EXECPTION("job has no associated processes");
        return;
    }
    if(jl.command_status == STOPPED) {
        PRINT_JOB_PROCESS_HEAD(index, ptr->pid, ptr->process_name, "stopped");
    } else {
        PRINT_JOB_PROCESS_HEAD(index, ptr->pid, ptr->process_name, "running");
    }
    ptr = ptr->next;
    while(ptr != NULL) {
        if(jl.command_status == STOPPED) {
            PRINT_JOB_PROCESS_NODE(ptr->pid, ptr->process_name, "stopped");
        } else {
            PRINT_JOB_PROCESS_NODE(ptr->pid, ptr->process_name, "running");
        }
        ptr = ptr->next;
    }
    return;
}