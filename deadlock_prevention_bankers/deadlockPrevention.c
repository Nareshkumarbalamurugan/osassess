#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3
int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool isSafeState(int processes[], int work[], bool finish[]) {
    int safeSequence[MAX_PROCESSES];
    int count = 0;
    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int p = 0; p < MAX_PROCESSES; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < MAX_RESOURCES; r++) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int r = 0; r < MAX_RESOURCES; r++)
                        work[r] += allocation[p][r];
                    safeSequence[count++] = processes[p];
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    printf("System is in a safe state. Safe sequence: ");
    for (int i = 0; i < MAX_PROCESSES; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
    return true;
}
bool requestResources(int processID, int request[]) {
    for (int r = 0; r < MAX_RESOURCES; r++) {
        if (request[r] > need[processID][r] || request[r] > available[r]) {
            printf("Request cannot be granted.\n");
            return false;
        }
    }
    for (int r = 0; r < MAX_RESOURCES; r++) {
        available[r] -= request[r];
        allocation[processID][r] += request[r];
        need[processID][r] -= request[r];
    }
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    for (int r = 0; r < MAX_RESOURCES; r++)
        work[r] = available[r];
    if (isSafeState((int[]){0,1,2,3,4}, work, finish)) {
        printf("Request granted.\n");
        return true;
    } else {
        printf("Request would lead to an unsafe state. Rolling back.\n");
        for (int r = 0; r < MAX_RESOURCES; r++) {
            available[r] += request[r];
            allocation[processID][r] -= request[r];
            need[processID][r] += request[r];
        }
        return false;
    }
}
int main() {
    int processes[MAX_PROCESSES] = {0, 1, 2, 3, 4};
    printf("Enter available resources: ");
    for (int i = 0; i < MAX_RESOURCES; i++)
        scanf("%d", &available[i]);
    printf("Enter max resources matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++){
        for (int j = 0; j < MAX_RESOURCES; j++)
            scanf("%d", &max[i][j]);
    }
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    for (int r = 0; r < MAX_RESOURCES; r++)
        work[r] = available[r];
    if (!isSafeState(processes, work, finish)) 
        printf("System is in an unsafe state!\n");
    int processID;
    int request[MAX_RESOURCES];
    printf("Enter process ID to request resources: ");
    scanf("%d", &processID);
    printf("Enter request for resources: ");
    for (int i = 0; i < MAX_RESOURCES; i++)
        scanf("%d", &request[i]);
    requestResources(processID, request);
    return 0;
}