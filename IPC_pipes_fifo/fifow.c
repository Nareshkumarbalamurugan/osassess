#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main() {
    int fd;
    char write_msg[] = "Hello from FIFO Writer!";
    fd = open("my_fifo", O_WRONLY);
    write(fd, write_msg, strlen(write_msg) + 1);
    close(fd);
    return 0;
}

