#include <stdio.h>
#define MAX 100

struct Process
{
    int id, at, bt, ct, wt, tat;
    int queue; // 0 = System, 1 = User
    int done;
};

int allDone(struct Process p[], int n)
{
    for (int i = 0; i < n; i++)
        if (!p[i].done)
            return 0;
    return 1;
}

int main()
{
    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i].id = i;
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);
        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].queue);
        p[i].done = 0;
    }

    int currentTime = 0;

    // 👉 Gantt storage
    int order[MAX];  // process index (-1 = IDLE)
    int time[MAX];   // time points
    int k = 0;

    time[k] = 0;

    // 👉 Scheduling + Gantt (single pass)
    while (!allDone(p, n))
    {
        int idx = -1;

        // System queue first
        for (int i = 0; i < n; i++)
        {
            if (!p[i].done && p[i].queue == 0 && p[i].at <= currentTime)
            {
                idx = i;
                break;
            }
        }

        // Then user queue
        if (idx == -1)
        {
            for (int i = 0; i < n; i++)
            {
                if (!p[i].done && p[i].queue == 1 && p[i].at <= currentTime)
                {
                    idx = i;
                    break;
                }
            }
        }

        if (idx == -1)
        {
            // CPU Idle
            order[k] = -1;
            currentTime++;
        }
        else
        {
            order[k] = idx;

            p[idx].wt = currentTime - p[idx].at;
            p[idx].ct = currentTime + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;

            currentTime = p[idx].ct;
            p[idx].done = 1;
        }

        k++;
        time[k] = currentTime;
    }

    // 👉 Print Gantt Chart
    printf("\nGantt Chart:\n");

    // Processes line
    for (int i = 0; i < k; i++)
    {
        if (order[i] == -1)
            printf("| IDLE ");
        else
            printf("| P%d ", p[order[i]].id);
    }
    printf("|\n");

    // Time line
    for (int i = 0; i <= k; i++)
    {
        printf("%-6d", time[i]);
    }
    printf("\n");

    // 👉 Results Table
    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].queue == 0 ? "System" : "User",
               p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
/*#include <stdio.h>

#define max 10
int arr[max][8];
    0- at
    1- bt
    2- ct
    3- wt
    4- tat
    5-done
    6-rt
    7-queue
void swap(int j){
    int t[8];
    for(int i=0;i<=7;i++){
        t[i]=arr[j][i];
        arr[j][i]=arr[j+1][i];
        arr[j+1][i]=t[i];
    }
}

void sort(int n){ //on basis of AT
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(arr[j][0] > arr[j+1][0])
                swap(j);
        }
    }
}

void MultiQueue(int n){
    int done =0;
    int t=0;
    float awt =0.0, atat=0.0;
    while(n>done){
        int id=-1, que=2;
        for(int i=0;i<n;i++){
            if(arr[i][5] != 1 && arr[i][0] <= t){
                if(arr[i][7] < que){
                    que=arr[i][7];
                    id =i;
                }
                else if (arr[i][7] == que)
                    if (arr[i][0] < arr[id][0]) id = i;

            }
        }

        if(id !=-1){
            arr[id][6]--;
            printf("P%d ,",id);
            if(arr[id][6]== 0){
                arr[id][2]=t+ 1;
                arr[id][4]= arr[id][2]-arr[id][0];
                arr[id][3]=arr[id][4]-arr[id][1];
                arr[id][5]=1;

                awt+= arr[id][3];
                atat+=arr[id][4];
                done++;
            }
        }
        else printf(" - ,");
        t++;

    }
    atat/=n;
    awt/=n;
    printf("\nAWT = %.2f \nATAT = %.2f",awt,atat);



}

void main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("s/s =0, user =1\n");
    for(int i=0;i<n;i++){
        printf("Process %d:\n",i);
        printf("Enter arrival time ,burst time and type :\n");
        scanf("%d",&arr[i][0]);
        scanf("%d",&arr[i][1]);
        scanf("%d",&arr[i][7]);
        arr[i][6]=arr[i][1];
    }
    sort(n);
    MultiQueue(n);
}*/
