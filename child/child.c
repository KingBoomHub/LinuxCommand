//功能：理解孤儿进程概念，fork进程后父进程退出，子进程变成孤儿进程并不断休眠打印
//注意：子进程变成孤儿进程后由Init进程继承，所以在终端中还是会不停的打印，这时候处于shell状态按Ctrl+c无法退出，需要另开终端，用kill命令杀掉孤儿进程才行

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    pid = fork();

    if (pid > 0) {
        printf("I am parent\n");
        exit(0);
    }
    else if (pid == 0) {
        while (1) {
            printf("I am child %d, my parent is %d\n", getpid(), getppid());
            sleep(3);
        }
    }
    else {
        perror("fork");
        exit(-1);
    }

    return 0;
}
