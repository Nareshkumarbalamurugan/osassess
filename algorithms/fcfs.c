#include<stdio.h>
#define MAX 100
typedef struct{
    int pid,at,bt,ct,tat,wt;
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
void FCFS(Process proc[],int n){
    Process temp;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if (proc[i].at > proc[j].at) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    int tot_tat=0,tot_wt=0,time=0;
    for(int i=0;i<n;i++){
        if(time<proc[i].at)
            time=proc[i].at;
        proc[i].ct=time+proc[i].bt;
        proc[i].tat=proc[i].ct-proc[i].at;
        proc[i].wt=proc[i].tat-proc[i].bt;
        tot_tat+=proc[i].tat;
        tot_wt+=proc[i].wt; 
        time=proc[i].ct;
    }
    printtable(proc,n);
    findavg(tot_wt,tot_tat,n);
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
    FCFS(proc,n);
}