//功能：打开文件，并重定向标准输入为该文件，加载upper实现字母大小写转换

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2) {
        fputs("wrapper file \n", stderr);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    
    dup2(fd, STDIN_FILENO); //重定向标准输入描述符为file文件的设备描述符

    close(fd);
    execl("./upper", "upper", NULL);
    perror("exec ./upper");
    exit(1);
}
