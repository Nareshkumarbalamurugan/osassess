#include <stdio.h>
#define MAX_BLOCKS 10
#define MAX_PROCESSES 20
void calculateWastage(int originalBlock[], int blocks, int processSize[], int allocation[], int processes) {
    int totalMem = 0, used = 0, internal = 0, external = 0, i;
    int usedBlocks[MAX_BLOCKS] = {0};
    for(i = 0; i < blocks; i++)
        totalMem += originalBlock[i];
    for(i = 0; i < processes; i++) {
        if(allocation[i] != -1) {
            used += processSize[i];
            internal += originalBlock[allocation[i]] - processSize[i];
            usedBlocks[allocation[i]] = 1;
        }
    }
    for(i = 0; i < blocks; i++) {
        if(!usedBlocks[i])
            external += originalBlock[i];
    }
    printf("\n--- Fragmentation Report ---\n");
    printf("Total Memory          : %d KB\n", totalMem);
    printf("Used Memory           : %d KB\n", used);
    printf("Internal Fragmentation: %d KB\n", internal);
    printf("External Fragmentation: %d KB\n", external);
    printf("Total Wasted Memory   : %d KB\n", internal + external);
}
void allocate(int blockSize[], int blocks, int processSize[], int processes, int allocation[]) {
    for(int i = 0; i < processes; i++) {
        if(allocation[i] != -1)
            printf("Process %d (%d KB) -> Block %d (%d KB)\n", i+1, processSize[i], allocation[i]+1, blockSize[allocation[i]]);
        else
            printf("Process %d (%d KB) -> Not Allocated\n", i+1, processSize[i]);
    }
    calculateWastage(blockSize, blocks, processSize, allocation, processes);
}
void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES], tempBlocks[MAX_BLOCKS], i, j;
    for(i = 0; i < blocks; i++)
        tempBlocks[i] = blockSize[i];
    for(i = 0; i < processes; i++)
        allocation[i] = -1;
    for(i = 0; i < processes; i++) {
        for(j = 0; j < blocks; j++) {
            if(tempBlocks[j] >= processSize[i]) {
                allocation[i] = j;
                tempBlocks[j] = -1;
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    allocate(blockSize, blocks, processSize, processes, allocation);
}
void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES], tempBlocks[MAX_BLOCKS], i, j, bestIdx;
    for(i = 0; i < blocks; i++)
        tempBlocks[i] = blockSize[i];
    for(i = 0; i < processes; i++)
        allocation[i] = -1;
    for(i = 0; i < processes; i++) {
        bestIdx = -1;
        for(j = 0; j < blocks; j++) {
            if(tempBlocks[j] >= processSize[i]) {
                if(bestIdx == -1 || tempBlocks[j] < tempBlocks[bestIdx])
                    bestIdx = j;
            }
        }
        if(bestIdx != -1) {
            allocation[i] = bestIdx;
            tempBlocks[bestIdx] = -1;
        }
    }
    printf("\nBest Fit Allocation:\n");
    allocate(blockSize, blocks, processSize, processes, allocation);
}
void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES], tempBlocks[MAX_BLOCKS], i, j, worstIdx;
    for(i = 0; i < blocks; i++)
        tempBlocks[i] = blockSize[i];
    for(i = 0; i < processes; i++)
        allocation[i] = -1;
    for(i = 0; i < processes; i++) {
        worstIdx = -1;
        for(j = 0; j < blocks; j++) {
            if(tempBlocks[j] >= processSize[i]) {
                if(worstIdx == -1 || tempBlocks[j] > tempBlocks[worstIdx])
                    worstIdx = j;
            }
        }
        if(worstIdx != -1) {
            allocation[i] = worstIdx;
            tempBlocks[worstIdx] = -1;
        }
    }
    printf("\nWorst Fit Allocation:\n");
    allocate(blockSize, blocks, processSize, processes, allocation);
}
int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int blocks = MAX_BLOCKS, processes, i, choice;
    printf("Enter sizes of 10 memory blocks:\n");
    for(i = 0; i < blocks; i++)
        scanf("%d", &blockSize[i]);
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &processes);
    if(processes > MAX_PROCESSES) {
        printf("Too many processes! Limit is %d.\n", MAX_PROCESSES);
        return 1;
    }
    printf("Enter sizes of %d processes:\n", processes);
    for(i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);
    printf("\n--- Memory Allocation Menu ---\n");
    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
    do {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                firstFit(blockSize, blocks, processSize, processes);break;
            case 2:
                bestFit(blockSize, blocks, processSize, processes);break;
            case 3:
                worstFit(blockSize, blocks, processSize, processes);break;
            case 4:
                printf("Exiting...\n");break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 4);
    return 0;
}
