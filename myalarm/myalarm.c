//使用alarm让计算机在1S里数数，测试计算机性能
#include <stdio.h>

int main(char argc, char *argv[])
{
	int counter = 0;
	alarm(1); //会产生SiGALRM信号，程序退出
	while(1) {
		printf("counter=%d\n", counter);
		counter ++;	
	}
}
