#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        execlp("/bin/ls", "ls", "-l", (char *)NULL);
        perror("exec failed");
        exit(1);
    } else
        printf("Parent process: PID = %d\n", getpid());
    return 0;
}

