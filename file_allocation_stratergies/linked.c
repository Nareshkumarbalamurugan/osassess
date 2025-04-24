#include <stdio.h>

#define MAX_BLOCKS 30

typedef struct {
    int index;
    int next;
} Block;

void linkedAllocation(int file[], int n) {
    int blocks[MAX_BLOCKS] = {0}; 
    for (int i = 0; i < n; i++) {
        if (blocks[file[i]] == 1) {
            printf("Block %d already allocated!\n", file[i]);
            return;
        }
        blocks[file[i]] = 1;
    }
    printf("File allocated using linked allocation: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", file[i]);
    }
    printf("NULL\n");
}

int main() {
    int file1[] = {3, 7, 8, 10};
    linkedAllocation(file1, 4);
    return 0;
}
