#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main()
{
    int n, m;

    // n = processes
    // m = resources

    int allocation[MAX][MAX];
    int request[MAX][MAX];
    int available[MAX];

    bool finish[MAX] = {false};

    int safeSeq[MAX];
    int count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Request Matrix
    printf("\nEnter Request Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    // Deadlock Detection Algorithm
    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canFinish = true;

                // Check if request <= available
                for (int j = 0; j < m; j++)
                {
                    if (request[i][j] > available[j])
                    {
                        canFinish = false;
                        break;
                    }
                }

                // Process can finish
                if (canFinish)
                {
                    for (int j = 0; j < m; j++)
                    {
                        available[j] += allocation[i][j];
                    }

                    finish[i] = true;

                    safeSeq[count] = i;
                    count++;

                    found = true;
                }
            }
        }

        // No process could proceed
        if (!found)
        {
            break;
        }
    }

    // Check for deadlock
    bool deadlock = false;

    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            deadlock = true;
            break;
        }
    }

    // Output
    if (!deadlock)
    {
        printf("\nNo Deadlock Detected.\n");

        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);

            if (i != n - 1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else
    {
        printf("\nDeadlock Detected.\n");

        printf("Processes involved in deadlock: ");

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                printf("P%d ", i);
            }
        }

        printf("\n");
    }

    return 0;
}
