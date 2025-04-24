#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        sleep(2); 
        printf("Child process exiting\n");
        exit(0); 
    } 
    else {
        int status;
        printf("Parent process: PID = %d\n", getpid());
        wait(&status);
        if (WIFEXITED(status))
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        else
            printf("Child process did not exit normally\n");
    }
    return 0;
}

