#include <stdio.h>

void indexedAllocation(int indexBlock, int blocks[], int n) {
    printf("Index Block: %d\n", indexBlock);
    printf("Allocated Blocks: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", blocks[i]);
    }
    printf("\n");
}

int main() {
    int blocks[] = {4, 7, 9};
    indexedAllocation(2, blocks, 3);
    return 0;
}
