//功能：调用pipe创建父写子读的通信管道进行通信
//注意：要先pipe再fork，这样pcb中的设备描述符也会复制过去得到继承

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int fd[2];    
    pid_t pid;
    char str[4096] = "Hello World"; //根据读时共享，写时复制原则，此处的str可以公用，不过真正使用时最好分开两个数组
    int len;
    
    //fd[0]写端，fd[1]读端
    if (pipe(fd) < 0) {
        perror("pipe fail\n");
        exit(1);
    }

    pid = fork();

    //方向：父写子读
    if (pid > 0) {
        printf("parent write\n");
        close(fd[0]); //关闭父读
        sleep(3);
        write(fd[1], str, strlen(str));
        wait(NULL);
    }
    else if (pid == 0) {
        printf("child read\n");
        close(fd[1]); //关闭子写
        len = read(fd[0], str, sizeof(str));
        write(STDOUT_FILENO, str, len);
    }
    else {
        perror("fork fail\n");
        exit(1);
    }
    
    return 0;
}
