#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
    int fd;
    char read_msg[100];
    fd = open("my_fifo", O_RDONLY);
    read(fd, read_msg, sizeof(read_msg));
    printf("Reader received: %s\n", read_msg);
    close(fd);
    return 0;
}

