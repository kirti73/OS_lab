#include <stdio.h>
struct process {
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
    int pr;
    int done;
    int rt;
};
void priorityP(struct process p[],int n)
{
    int t=0;
    int completed=0;
    float atat=0.0f,awt=0.0f;
    while(completed<n)
    {

        int idx=-1;
        int highest_priority=9999;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].done == 0)
            {
                if (p[i].pr < highest_priority)
                {
                    highest_priority = p[i].pr;
                    idx = i;
                }
                else if (p[i].pr == highest_priority && idx!=-1)
                {
                        if (p[i].at < p[idx].at)

                        {
                            idx = i;
                        }
                }
            }
        }
        if(idx!=-1)
        {
            p[idx].rt--;
            t++;
            if (p[idx].rt == 0)
            {
                completed++;
                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].done = 1;
                atat += p[idx].tat;
              awt += p[idx].wt;
            }
        }
        else
        {
            t++;
        }
    }
    printf("\n%-5s %-5s %-5s %-5s %-5s %-5s %-5s\n","PID","AT","BT","CT","WT","TAT","PRIORITY");
    for(int idx=0;idx<n;idx++)
    {
        printf("%5d %5d %5d %5d %5d %5d %5d\n",idx+1,p[idx].at,p[idx].bt,p[idx].ct,p[idx].wt,p[idx].tat,p[idx].pr);
    }
    printf("Average waiting time : %.2f\n",awt/n);
    printf("Average turnaround time : %.2f\n",atat/n);

}
int main()
{
    int n;
    printf("Enter no. of process:");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        printf("arrival time:");
        scanf("%d",&p[i].at);
        printf("burst time:");
        scanf("%d",&p[i].bt);
        printf("priority:");
        scanf("%d",&p[i].pr);
        p[i].done=0;
        p[i].rt = p[i].bt;
    }
    priorityP(p,n);

}
