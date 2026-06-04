#include <stdio.h>
#include <stdbool.h>

#define MAX 100

// FIFO Page Replacement
void fifo(int pg[], int n, int cap)
{
    int fm[MAX];
    int f = 0, cnt = 0, flt = 0;

    printf("\n--- FIFO Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        bool fnd = false;

        for (int j = 0; j < cnt; j++)
        {
            if (fm[j] == pg[i])
            {
                fnd = true;
                break;
            }
        }

        if (!fnd)
        {
            if (cnt < cap)
            {
                fm[cnt++] = pg[i];
            }
            else
            {
                fm[f] = pg[i];
                f = (f + 1) % cap;
            }
            flt++;
        }

        printf("Page %d -> [", pg[i]);
        for (int j = 0; j < cnt; j++)
        {
            printf("%d", fm[j]);
            if (j < cnt - 1)
                printf(" ");
        }
        printf("]\n");
    }

    printf("Total Page flt (FIFO): %d\n", flt);
}

// LRU Page Replacement
void lru(int pg[], int n, int cap)
{
    int fm[MAX];
    int cnt = 0, flt = 0;

    printf("\n--- LRU Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        bool fnd = false;

        for (int j = 0; j < cnt; j++)
        {
            if (fm[j] == pg[i])
            {
                fnd = true;

                // Move page to end (most recently used)
                for (int k = j; k < cnt - 1; k++)
                    fm[k] = fm[k + 1];

                fm[cnt - 1] = pg[i];
                break;
            }
        }

        if (!fnd)
        {
            if (cnt < cap)
            {
                fm[cnt++] = pg[i];
            }
            else
            {
                // Remove least recently used page
                for (int k = 0; k < cap - 1; k++)
                    fm[k] = fm[k + 1];

                fm[cap - 1] = pg[i];
            }

            flt++;
        }

        printf("Page %d -> [", pg[i]);
        for (int j = 0; j < cnt; j++)
        {
            printf("%d", fm[j]);
            if (j < cnt - 1)
                printf(" ");
        }
        printf("]\n");
    }

    printf("Total Page flt (LRU): %d\n", flt);
}

// Optimal Page Replacement
void optimal(int pg[], int n, int cap)
{
    int fm[MAX];
    int cnt = 0, flt = 0;

    printf("\n--- Optimal Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        bool fnd = false;

        for (int j = 0; j < cnt; j++)
        {
            if (fm[j] == pg[i])
            {
                fnd = true;
                break;
            }
        }

        if (!fnd)
        {
            if (cnt < cap)
            {
                fm[cnt++] = pg[i];
            }
            else
            {
                int farthest = -1;
                int idx = -1;

                for (int j = 0; j < cap; j++)
                {
                    int k;

                    for (k = i + 1; k < n; k++)
                    {
                        if (fm[j] == pg[k])
                            break;
                    }

                    if (k > farthest)
                    {
                        farthest = k;
                        idx = j;
                    }
                }

                fm[idx] = pg[i];
            }

            flt++;
        }

        printf("Page %d -> [", pg[i]);
        for (int j = 0; j < cnt; j++)
        {
            printf("%d", fm[j]);
            if (j < cnt - 1)
                printf(" ");
        }
        printf("]\n");
    }

    printf("Total Page flt (Optimal): %d\n", flt);
}

int main()
{
    int n, cap;
    int pg[MAX];

    printf("Enter number of pg: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of pg!\n");
        return 1;
    }

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pg[i]);
    }

    printf("Enter number of fm: ");
    scanf("%d", &cap);

    if (cap <= 0 || cap > MAX)
    {
        printf("Invalid frame size!\n");
        return 1;
    }

    fifo(pg, n, cap);
    lru(pg, n, cap);
    optimal(pg, n, cap);

    return 0;
}
