#include <stdio.h>
#include <string.h>

int getEmptySeat(int seat[20][5], int n)
{
    int count = 0;

    for (int i = 0; i < 5; i++)
    {
        if (seat[n][i] != 0)
        {
            count++;
        }
    }

    return count;
}

int main()
{
    int seat[20][5];
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            seat[i][j] = 5 * i + j + 1;
        }
    }

    int n, num[100];
    scanf("%d", &n);
    for (int i = 0; i <n; i++)
    {
        scanf("%d", &num[i]);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            int remain = getEmptySeat(seat, j);
            if (num[i] <= remain)
            {
                for (int k = 0; k < num[i]; k++)
                {
                    printf("%d ", seat[j][5 - remain + k]);
                    seat[j][5 - remain + k] = 0;
                }
                printf("\n");
                break;
            }
        }
    }

    return 0;
}