//功能：结合access实现查看文件是否存在，读写执行等权限

#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>   
#include <fcntl.h>   

int main(int argc, char *argv[])   
{   
    if((access(argv[1], F_OK)) != -1) {   
        printf("文件存在.\n");   
    }   
    else {   
        printf("文件不存在!\n");   
    }   

    if(access(argv[1], R_OK) != -1) {   
        printf("文件有可读权限\n");   
    }   
    else {   
        printf("文件不可读.\n");   
    }   

    if(access(argv[1], W_OK) != -1) {   
        printf("文件有可写权限\n");   
    } 
    else {   
        printf("文件不可写.\n");   
    }   

    if(access(argv[1], X_OK) != -1) {   
        printf("文件有可执行权限\n");   
    }   
    else {   
        printf("文件不可执行.\n");   
    }   

    return 0;   
}  
