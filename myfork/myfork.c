//使用fork函数创建父进程和子进程，理解进程概念
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    pid_t pid; //进程编号

    pid = fork(); //fork调用1次返回2次，在父进程中返回子进程的PID号，在子进程返回0

    if (pid > 0) {
        while(1) {
            printf("I am parent pid=%d \n", pid);
            sleep(1);
        }
    }
    else if (pid == 0) {
        while(1) {
            printf("I am child pid=%d \n", pid);
            sleep(3);
        }
    }
    else {
        perror("fork error");
        exit(1);
    }

    return 0;
}
