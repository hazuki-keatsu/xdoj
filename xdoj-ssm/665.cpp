#include <stdio.h>
#include <stdlib.h>

void sort(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int *arr = (int *)malloc((m * n) * sizeof(int));
    if (arr == NULL)
        return 1;

    for (int i = 0; i < (m * n); i++)
    {
        scanf("%d", &arr[i]);
    }

    sort(arr, m * n);

    int out[8][8] = {0};

    int k = 0;
    for (int i = 0; i < n; i++) // 水平
    {
        if (i % 2 == 0)
        {
            for (int j = m - 1; j >= 0; j--) // 垂直
            {
                out[j][i] = arr[k];
                k++;
            }
        }
        else 
        {
            for (int j = 0; j < m; j++) // 垂直
            {
                out[j][i] = arr[k];
                k++;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", out[i][j]);
        }
        printf("\n");
    }
    

    free(arr);
    return 0;
}