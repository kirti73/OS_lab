#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct Process {
    int id;
    int bt;
    int deadline;  // For EDF
    int period;    // For RMS
    int share;     // For Proportional
    int ct, wt, tat;
};

void resetProcesses(struct Process p[], int n) {
    for (int i = 0; i < n; i++)
        p[i].ct = p[i].wt = p[i].tat = 0;
}

// -------- Gantt Chart Printer --------
void printGantt(int gantt[], int times[], int len) {
    printf("\nGantt Chart:\n");

    // Top border
    printf(" ");
    for (int i = 0; i < len; i++) {
        printf("+-------");
    }
    printf("+\n");

    // Process IDs
    printf(" ");
    for (int i = 0; i < len; i++) {
        if (gantt[i] == -1)
            printf("|  IDLE ");
        else
            printf("|  P%-4d", gantt[i]);
    }
    printf("|\n");

    // Bottom border
    printf(" ");
    for (int i = 0; i < len; i++) {
        printf("+-------");
    }
    printf("+\n");

    // Time labels
    printf("%-2d", times[0]);
    for (int i = 0; i < len; i++) {
        printf("      %-3d", times[i + 1]);
    }
    printf("\n");
}

// -------- 1. EDF Scheduling --------
void EDF(struct Process p[], int n) {
    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");

    // Sort by deadline
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (p[j].deadline > p[j + 1].deadline) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    int gantt[MAX], times[MAX + 1];
    int len = 0, time = 0;

    for (int i = 0; i < n; i++) {
        gantt[len] = p[i].id;
        times[len] = time;
        len++;

        p[i].wt = time;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - 0; // arrival = 0
    }
    times[len] = time;

    printGantt(gantt, times, len);

    printf("\nID\tBT\tDeadline\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
}

// -------- 2. Rate Monotonic Scheduling (RMS) --------
void RMS(struct Process p[], int n) {
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");

    // Sort by period (lower period = higher priority)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (p[j].period > p[j + 1].period) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    int gantt[MAX], times[MAX + 1];
    int len = 0, time = 0;

    for (int i = 0; i < n; i++) {
        gantt[len] = p[i].id;
        times[len] = time;
        len++;

        p[i].wt = time;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
    }
    times[len] = time;

    printGantt(gantt, times, len);

    printf("\nID\tBT\tPeriod\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
}

// -------- 3. Proportional Share Scheduling --------
void ProportionalShare(struct Process p[], int n) {
    printf("\n===== Proportional Share Scheduling =====\n");

    int totalShare = 0;
    for (int i = 0; i < n; i++)
        totalShare += p[i].share;

    int remaining[MAX];
    for (int i = 0; i < n; i++)
        remaining[i] = p[i].bt;

    // Build Gantt chart via weighted round-robin
    // Each round, process i gets (share/totalShare) fraction of CPU
    // We simulate by giving each process 'share' time units per round
    int gantt[MAX * 100], times[MAX * 100 + 1];
    int len = 0, time = 0, done = 0;

    while (done < n) {
        int progressed = 0;
        for (int i = 0; i < n; i++) {
            if (remaining[i] <= 0) continue;

            // Give process i exactly 'share' slots of 1 unit each this round
            for (int s = 0; s < p[i].share && remaining[i] > 0; s++) {
                // Add to Gantt (merge consecutive same-process slots)
                if (len > 0 && gantt[len - 1] == p[i].id) {
                    times[len]++;  // extend last block by 1
                } else {
                    gantt[len] = p[i].id;
                    times[len] = time;
                    len++;
                    times[len] = time + 1;
                }

                time++;
                remaining[i]--;
                progressed = 1;

                if (remaining[i] == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct;
                    p[i].wt = p[i].tat - p[i].bt;
                    done++;
                }
            }
        }
        if (!progressed) break;
    }

    printGantt(gantt, times, len);

    printf("\nID\tBT\tShare\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].share,
               p[i].ct, p[i].wt, p[i].tat);
}

// -------- Main --------
int main() {
    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("  Burst Time           : "); scanf("%d", &p[i].bt);
        printf("  Deadline  (for EDF)  : "); scanf("%d", &p[i].deadline);
        printf("  Period    (for RMS)  : "); scanf("%d", &p[i].period);
        printf("  Share     (for PS)   : "); scanf("%d", &p[i].share);
    }

    struct Process copy[MAX];

    // EDF
    memcpy(copy, p, n * sizeof(struct Process));
    resetProcesses(copy, n);
    EDF(copy, n);

    // RMS
    memcpy(copy, p, n * sizeof(struct Process));
    resetProcesses(copy, n);
    RMS(copy, n);

    // Proportional Share
    memcpy(copy, p, n * sizeof(struct Process));
    resetProcesses(copy, n);
    ProportionalShare(copy, n);

    return 0;
}