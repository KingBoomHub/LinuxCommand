//功能：调用pipe创建父写子读的通信管道进行通信
//注意：要先pipe再fork，这样pcb中的设备描述符也会复制过去得到继承

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
    int fd[2];    
    pid_t pid;
    char str[4096] = "Hello World\n"; //根据读时共享，写时复制原则，此处的str可以公用，不过真正使用时最好分开两个数组
    int len;
    int flags;
    
    //fd[0]写端，fd[1]读端
    if (pipe(fd) < 0) {
        perror("pipe fail\n");
        exit(1);
    }
    printf("pipe buff max=%ld", fpathconf(fd[0], _PC_PIPE_BUF)); 

    pid = fork();

    //方向：父写子读
    if (pid > 0) {
        printf("parent write\n");
        close(fd[0]); //关闭父读
        sleep(5);
        write(fd[1], str, strlen(str));
        close(fd[1]); //用完写后及时关闭读端口
        wait(NULL);
    }
    else if (pid == 0) {
        printf("child read\n");
        close(fd[1]); //关闭子写

        //默认管道为阻塞模式，可通过fcntl配置为非阻塞模式（读出之前状体后在配置标志位设置回去）
        flags = fcntl(fd[0], F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(fd[0], F_SETFL, flags);
tryagain:
        len = read(fd[0], str, sizeof(str));
        if (len == -1) {
            if (errno == EAGAIN) { //目前是非阻塞状体，读到阻塞状态，errno值报错
                perror("read fail");
            }
            write(STDOUT_FILENO, "try again\n", 10);
            sleep(1);
            goto tryagain;
        }
        write(STDOUT_FILENO, str, len);
        close(fd[0]); //用完读后及时关闭写端口
    }
    else {
        perror("fork fail\n");
        exit(1);
    }
    
    return 0;
}
