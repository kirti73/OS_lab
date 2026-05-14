#include <stdio.h>
#include <stdbool.h>
#define MAX_P 10
#define MAX_R 10
// Function to check SAFE state
bool isSafe(
    int n,
    int m,
    int allocation[MAX_P][MAX_R],
    int need[MAX_P][MAX_R],
    int available[MAX_R],
    int safeSeq[MAX_P]
)
{
    int work[MAX_R];
    bool finish[MAX_P] = {false};

    // work = available
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canFinish = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int n, m;

    int allocation[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];

    int available[MAX_R];
    int safeSeq[MAX_P];

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

    // Maximum Matrix
    printf("\nEnter Maximum Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    // Need Matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initial Safety Check
    if (isSafe(n, m, allocation, need, available, safeSeq))
    {
        printf("\nSystem is in SAFE state.\n");

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
        printf("\nSystem is in UNSAFE state.\n");
        return 0;
    }

    // Resource Request
    int p, request[MAX_R];

    printf("\nEnter process number: ");
    scanf("%d", &p);

    printf("Enter request vector:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &request[i]);
    }

    // Check request <= need
    for (int i = 0; i < m; i++)
    {
        if (request[i] > need[p][i])
        {
            printf("\nError: Request exceeds maximum need.\n");
            return 0;
        }
    }

    // Check request <= available
    for (int i = 0; i < m; i++)
    {
        if (request[i] > available[i])
        {
            printf("\nResources not available.\n");
            return 0;
        }
    }

    // Temporary Allocation
    for (int i = 0; i < m; i++)
    {
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }

    // Check safety again
    if (isSafe(n, m, allocation, need, available, safeSeq))
    {
        printf("\nRequest CAN be granted.\n");
        printf("System remains SAFE.\n");

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
        // Rollback directly
        for (int i = 0; i < m; i++)
        {
            available[i] += request[i];
            allocation[p][i] -= request[i];
            need[p][i] += request[i];
        }

        printf("\nRequest CANNOT be granted.\n");
        printf("System would become UNSAFE.\n");
    }

    return 0;
}
