#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    int pid;
    int n;
    int i;
    pid = fork();
    if(pid == 0)
    {
        n = 1;
    }
    else
        n = 51;
    if(pid != 0)
        wait(NULL);
    i = n;
    while(i < n + 50)
    {
        printf("%d ", i);
        i++;
    }
    if(pid != 0)
        printf("\n");

}