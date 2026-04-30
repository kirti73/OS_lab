#include <stdio.h>
#define MAX 10
#define SIM_TIME 20
#include <math.h>
typedef struct {
    int id;
    int exec_time;
    int period;
    int remaining_time;
    int next_release;
    int total_executed;
} Process;

Process p[MAX];
int n;

// Pick process with smallest period (highest priority)
int get_highest_priority() {
    int i, idx = -1;
    int min_period = 1e9;

    for (i = 0; i < n; i++) {
        if (p[i].remaining_time > 0) {
            if (p[i].period < min_period) {
                min_period = p[i].period;
                idx = i;
            }
        }
    }
    return idx;
}

void check_liu_util(Process p[], int n) {
    float U = 0;
    int i;

    for (i = 0; i < n; i++) {
        U += (float)p[i].exec_time / p[i].period;
    }

    float bound = n * (pow(2, 1.0/n) - 1);

    printf("\nTotal Utilization U = %.2f\n", U);
    printf("Liu Bound = %.2f\n", bound);

    if (U <= bound)
        printf("Schedulable (Guaranteed by Liu & Layland)\n");
    else
        printf("Not guaranteed schedulable\n");

    if (U > 1.0)
        printf("Definitely NOT schedulable (U > 1)\n");
}
void print_gantt(Process p[], int n, int st) {
    int t, i;

    // Print time axis
    printf("\nTime:");
    for (t = 0; t <= st; t++) {
        printf("%3d ", t);
    }
    printf("\nTask : ");
    // Simulation loop
    for (t = 0; t < st; t++) {

        // Release jobs
        for (i = 0; i < n; i++) {
            if (t == p[i].next_release) {
                p[i].remaining_time = p[i].exec_time;
                p[i].next_release += p[i].period;
            }
        }

        // Pick highest priority (smallest period)
        int idx = get_highest_priority();
        // int min_period = 1e9;

        // for (i = 0; i < n; i++) {
        //     if (p[i].remaining_time > 0 && p[i].period < min_period) {
        //         min_period = p[i].period;
        //         idx = i;
        //     }
        // }

        // Execute
        if (idx == -1) {
            printf("| I ");
        } else {
            printf("|P%d ", p[idx].id);
            p[idx].remaining_time--;
            p[idx].total_executed++;
        }
    }

    printf("|\n");
}

int main() {
    int i, t;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Process %d execution time: ", i + 1);
        scanf("%d", &p[i].exec_time);

        printf("Process %d period: ", i + 1);
        scanf("%d", &p[i].period);

        p[i].id = i + 1;
        p[i].remaining_time = 0;
        p[i].next_release = 0;
        p[i].total_executed = 0;
    }
    printf("\nUtilisation:\t");check_liu_util(p,n);
    printf("\nGantt Chart:\n");

    print_gantt(p,n,SIM_TIME);
    

    return 0;
}
