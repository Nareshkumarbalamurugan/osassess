#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from Parent!";
    char read_msg[100];
    if (pipe(fd) == -1) {  
        perror("Pipe failed");
        return 1;
    }
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    if (pid > 0) {
        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
    } 
    else {
        close(fd[1]);
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);
    }
    return 0;
}
