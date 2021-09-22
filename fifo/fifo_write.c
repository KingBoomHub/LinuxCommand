//功能：设计fifo管道的收发端，并进行通信
//这是写端进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void sys_err(char *str, int errnum)
{
    perror(str);
    exit(errnum);
}

int main(int argc, char *argv[])
{
    int fd;
    char str[4096] = "HelloWorld\n";
    int cnt;

    if (argc < 2) {
        printf("please fill file\n");
        exit(1);
    }

    fd = open(argv[1], O_WRONLY); //打开管道(Linux下一切皆文件)
    if (fd < 0) {
        sys_err("open", 1);
    }

    write(fd, str, strlen(str));
    close(fd);

    return 0;
}

