#include<stdio.h>
#include <stdbool.h>
#define MAX 100
typedef struct{
    int pid,at,bt,ct,tat,wt;
    bool completed;
}Process;
void printtable(Process proc[],int n){
    printf("Process\tArrival\t  Burst\t  Completion\tTAT\twaiting\n");
   for(int i=0;i<n;i++){
   printf("P%d\t%5d\t%6d\t%6d\t%10d\t%6d\n",proc[i].pid,proc[i].at,proc[i].bt,proc[i].ct,proc[i].tat,proc[i].wt);
    }
}
void findavg(int i,int j,int n){
    printf("Average waiting time : %.2f\n",(float)i/n);
    printf("Average TurnAroundTime : %.2f\n",(float)j/n);
}
void ROUND_ROBIN(Process proc[], int n, int quantum) {
    int tot_wt = 0, tot_tat = 0, time = 0, completed = 0;
    int remaining_bt[MAX]; 
    for (int i = 0; i < n; i++)  
        remaining_bt[i] = proc[i].bt;
    while (completed < n) {
        int idle = 1; 
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && proc[i].at <= time) {  
                idle = 0;  
                if (remaining_bt[i] > quantum) {  
                    time += quantum;
                    remaining_bt[i] -= quantum;
                } else {  
                    time += remaining_bt[i];  
                    proc[i].ct = time;  
                    proc[i].tat = proc[i].ct - proc[i].at;  
                    proc[i].wt = proc[i].tat - proc[i].bt;  
                    tot_tat += proc[i].tat;
                    tot_wt += proc[i].wt;
                    remaining_bt[i] = 0;  
                    completed++;  
                }
            }
        }
        if (idle) 
            time++;
    }
    printtable(proc, n);
    findavg(tot_wt, tot_tat, n);
}
int main(){
    int n,quantum;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("Enter quantum(in ms): ");
    scanf("%d",&quantum);
    Process proc[MAX];
    for (int i=0;i<n;i++){
        proc[i].pid=i+1;
        printf("Enter arrival time and burst time for %d : ",proc[i].pid);
        scanf("%d %d", &proc[i].at, &proc[i].bt);
    }
    ROUND_ROBIN(proc,n,quantum);
}