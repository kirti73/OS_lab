#include <stdio.h>
struct process{
    int at,bt,wt,tat,rt,done,ct;
};
#define max 10
int rr(struct process p[],int n,int tq)
{
    int completed=0,t=0;
    float awt=0.0f,atat=0.0;
    int q[max],f=0,r=0,visited[max]={0};
    for(int i=0;i<n;i++)
    {
        if (p[i].at==0)
        {
            q[r]=i;
            visited[i]=1;
        }
    }
    if(r==0)
    {
        int min_t=p[0].at,idx=0;
        for(int i=1;i<n;i++)
    {
        if (p[i].at<min_t)
        {
            min_t=p[i].at;
            idx=i;
        }
    }
    t=p[idx].at;
    q[r++]=idx;
    visited[idx]=1;
    }
    while (completed<n)
    {   int idx=q[f++];
        if (p[idx].rt>0)
        {
            if(p[idx].rt>tq)
            {
                t+=tq;
                p[idx].rt-=tq;
            }
            else
            {
                t += p[idx].rt;
                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].rt = 0;
                completed++;
            }
            for (int i = 0; i < n; i++)
                {
                    if (i != idx && !visited[i] && p[i].at <= t)
                    {
                        q[r++] = i;
                        visited[i] = 1;
                    }
                }
            if (p[idx].rt > 0)
                {
                    q[r++] = idx;
                }
            if (f == r && completed < n)
            {
                for (int i = 0; i < n; i++)
                {
                    if (!visited[i])
                    {
                        q[r++] = i;
                        visited[i] = 1;
                        t = p[i].at > t ? p[i].at : t;
                        break;
                    }
                }
            }
        }

       /* for(int i=0;i<n;i++)
        {
            if (t<p[i].at)
            {
                t+=q;
            }
            else if(t==p[i].at)&& p[i].done==0)
            {
                p[i].
            }
        }*/
    }
        printf("\nID\tAT\tBT\tCT\tWT\tTAT\n");
        float total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
            total_wt += p[i].wt;
            total_tat += p[i].tat;
        }
        printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
        printf("Average Turnaround Time: %.2f\n", total_tat / n);
}
int main()
{
    int n;
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        printf("arrival time:");
        scanf("%d",&p[i].at);
        printf("burst time:");
        scanf("%d",&p[i].bt);
        p[i].done=0;
        p[i].rt = p[i].bt;
    }
    int q;
    printf("Enter time quantum:");
    scanf("%d",&q);
    rr(p,n,q);
}
