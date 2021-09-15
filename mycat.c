//功能：实现Linux下的cat功能
//1.打开文件并输出内容到终端显示
//2.回显输入的内容

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;
    int readcnt;
    char buff[4096];
    
    if (argc < 2) {
        printf("mycat please filename\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY); //打开文件并设置只读模式，记录该文件的设备描述符	
    readcnt = read(fd, buff, sizeof(buff)); //根据文件设备描述符，读取文件数据到buff中，并统计数据长度
    write(1, buff, readcnt); //向屏幕写入buff中的数据

    close(fd);
    
    return 0;
}
