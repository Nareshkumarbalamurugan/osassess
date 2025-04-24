#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1); 
    }
    if (pid == 0) {  
        printf("Child process (PID: %d) running...\n", getpid());
        sleep(2);
        printf("Child process exiting.\n");
        exit(0);
    } else {  
        printf("Parent process (PID: %d) waiting for child...\n", getpid());
        sleep(3);
        printf("Parent process exiting.\n");
        exit(0); 
    }
}
