#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0)
        printf("This is the child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    else
        printf("This is the parent process: PID = %d\n", getpid());
    return 0;
}

