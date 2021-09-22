//功能：设计fifo管道的收发端，并进行通信
//这是读端进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sys_err(char *str, int errnum)
{
    perror(str);
    exit(errnum);
}

int main(int argc, char *argv[])
{
    int fd;
    char str[4096];
    int cnt;

    if (argc < 2) {
        printf("please fill file\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY); //打开管道(Linux下一切揭文件)
    if (fd < 0) {
        sys_err("open", 1);
    }

    cnt = read(fd, str, sizeof(str));
    write(STDOUT_FILENO, str, cnt);
    close(fd);

    return 0;
}

