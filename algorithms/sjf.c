#include<stdio.h>
#include <stdbool.h>
#define MAX 100
typedef struct{
    int pid,at,bt,ct,tat,wt;
    bool completed;
}Process;
void printtable(Process proc[],int n){
    printf("Process\tArrival\tBurst\tCompletion\tTAT\t\twaiting\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%5d\t%6d\t%6d\t%10d\t%6d\n",proc[i].pid,proc[i].at,proc[i].bt,proc[i].ct,proc[i].tat,proc[i].wt);
    }
}
void findavg(int i,int j,int n){
    printf("Average waiting time : %.2f\n",(float)i/n);
    printf("Average TurnAroundTime : %.2f\n",(float)j/n);
}
void SJF(Process proc[], int n) {
    int completed = 0, time = 0, tot_wt = 0, tot_tat = 0;
    for (int i = 0; i < n; i++)
        proc[i].completed = false;
    while (completed < n) {
        int shortest_index = -1;
        int shortest_bt = MAX;
        for (int i = 0; i < n; i++) {
            if (!proc[i].completed && proc[i].at <= time) {
                if (proc[i].bt < shortest_bt) {
                    shortest_bt = proc[i].bt;
                    shortest_index = i;
                }
            }
        }
        if (shortest_index == -1)
            time++;
        else {
            proc[shortest_index].ct = time + proc[shortest_index].bt;
            proc[shortest_index].tat = proc[shortest_index].ct - proc[shortest_index].at;
            proc[shortest_index].wt = proc[shortest_index].tat - proc[shortest_index].bt;
            tot_tat += proc[shortest_index].tat;
            tot_wt += proc[shortest_index].wt;
            proc[shortest_index].completed = true;
            completed++;
            time = proc[shortest_index].ct;
        }
    }
    printtable(proc, n);
    findavg(tot_wt, tot_tat, n);
}
int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    Process proc[MAX];
    for (int i=0;i<n;i++){
        proc[i].pid=i+1;
        printf("Enter arrival time and burst time for %d : ",proc[i].pid);
        scanf("%d %d", &proc[i].at, &proc[i].bt);
    }
    SJF(proc,n);
}