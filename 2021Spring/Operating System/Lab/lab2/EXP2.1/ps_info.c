#include<unistd.h>
#include<sys/syscall.h>
#include<stdio.h>
int main(void)
{
	int num;
	int i = 0;
	int pid[100];
	long long int time[100];
	syscall(333, &num, pid, time);
	printf("process number is %d\n",num);
	printf("PID     TIME\n");
	for(i = 0; i < num; i++)
	{
		printf("%-8d%lld\n", pid[i], time[i]);
	}
	return 0;
}

