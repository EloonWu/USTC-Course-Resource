#include<unistd.h>
#include<sys/syscall.h>
#include<stdio.h>
int main()
{
    int result;
    int pid_list[256];
    char name_list[256][100];
    int i;
    syscall(333, &result, &pid_list, &name_list);
    printf("process number is : %d\n", result);
    printf("PID         COMMAND\n");
    for(i = 0; i < result; i++)
    {
        printf("%-12d", pid_list[i]);
        printf("%s\n", name_list[i]);
    }
    return 0;
}