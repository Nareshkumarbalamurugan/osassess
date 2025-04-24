#include<stdio.h>
#define MAX 100
typedef struct{
    int pid,at,bt,ct,tat,wt,priority;
}Process;
void printtable(Process proc[],int n){
    printf("Priority Process Arrival  Burst Completion\tTAT\twaiting\n");
    for(int i=0;i<n;i++){
        printf("%d\t P%d\t%5d\t%6d\t%6d\t%10d\t%6d\n",proc[i].priority,proc[i].pid,proc[i].at,proc[i].bt,proc[i].ct,proc[i].tat,proc[i].wt);
    }
}
void findavg(int i,int j,int n){
    printf("Average waiting time : %.2f\n",(float)i/n);
    printf("Average TurnAroundTime : %.2f\n",(float)j/n);
}
void PRIORITY(Process proc[],int n){
    Process temp;
    int tot_wt = 0, tot_tat = 0, time = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority || 
               (proc[i].priority == proc[j].priority && proc[i].at > proc[j].at)) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (time < proc[i].at)  
            time = proc[i].at; 
        proc[i].ct = time + proc[i].bt; 
        proc[i].tat = proc[i].ct - proc[i].at;  
        proc[i].wt = proc[i].tat - proc[i].bt;  
        tot_tat += proc[i].tat;
        tot_wt += proc[i].wt;
        time = proc[i].ct;
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
        printf("Enter arrival time and burst time and priority for P%d: ",proc[i].pid);
        scanf("%d %d %d", &proc[i].at, &proc[i].bt, &proc[i].priority);
    }
    PRIORITY(proc,n);
}