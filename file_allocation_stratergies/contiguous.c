#include <stdio.h>

#define MAX_FILES 10

typedef struct {
    int start, length;
} File;

void contiguousAllocation(File files[], int n) {
    int memory[30] = {0}; // Assuming 100 blocks of memory
    for (int i = 0; i < n; i++) {
        int start = files[i].start;
        int length = files[i].length;
        int allocated = 1;
        for (int j = start; j < start + length; j++) {
            if (memory[j] == 1) {
                allocated = 0;
                break;
            }
        }
        if (allocated) {
            for (int j = start; j < start + length; j++)
                memory[j] = 1;
            printf("File %d allocated from block %d to %d\n", i + 1, start, start + length - 1);
        } else {
            printf("File %d cannot be allocated\n", i + 1);
        }
    }
}

int main() {
    File files[MAX_FILES] = {{2, 3}, {5, 4}, {12, 2}};
    int n = 3;
    contiguousAllocation(files, n);
    return 0;
}
