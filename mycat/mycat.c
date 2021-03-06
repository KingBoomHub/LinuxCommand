//功能：实现Linux下的cat功能
//1.回显输入的内容
//2.打开文件并输出内容到终端显示

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    int readcnt;
    char buff[4096];
    
    //回显模式
    if (argc < 2) {
        while(1) 
        {
            readcnt = read(STDIN_FILENO, buff, 10);
            if (readcnt < 0) {
                perror("read STDIN_FILENO");
                exit(1);
            }
            write(STDOUT_FILENO, buff, readcnt);
        }
    }

    //文件显示模式
    fd = open(argv[1], O_RDONLY); //打开文件并设置只读模式，记录该文件的设备描述符	
    readcnt = read(fd, buff, sizeof(buff)); //根据文件设备描述符，读取文件数据到buff中，并统计数据长度
    write(1, buff, readcnt); //向屏幕写入buff中的数据

    close(fd);
    
    return 0;
}
