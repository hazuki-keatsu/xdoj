#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void filter(int *datain, int *dataout, int n);

int main()
{
    int n;
    scanf("%d", &n);
    int *x = (int *)malloc(n * n * sizeof(int));
    int *y = (int *)calloc(n * n, sizeof(int));
    for (int i = 0; i < n * n; i++)
    {
        scanf("%d", &x[i]);
    }

    filter(x, y, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", y[i * n + j]);

        }
        printf("\n");
    }
    

    return 0;
}

void filter(int *datain, int *dataout, int n)
{
    int sum;


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sum = 0;
            if (i > 0 && i < n - 1 && j > 0 && j < n - 1)
            {
                for (int y = -1; y <= 1; y++)
                {
                    for (int x = -1; x <= 1; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test1\n");
            }
            else if (i == 0 && j == 0 && i != n - 1 && j != n - 1)
            {
                for (int y = 0; y <= 1; y++)
                {
                    for (int x = 0; x <= 1; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test2\n");
            }
            else if (i == 0 && j == n - 1 && i != n - 1 && j != 0)
            {
                for (int y = 0; y <= 1; y++)
                {
                    for (int x = -1; x <= 0; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test3\n");
            }
            else if (i == n - 1 && j == 0 && i != 0 && j != n - 1)
            {
                for (int y = -1; y <= 0; y++)
                {
                    for (int x = 0; x <= 1; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test4\n");
            }
            else if (i == n - 1 && j == n - 1 && i != 0 && j != 0)
            {
                for (int y = -1; y <= 0; y++)
                {
                    for (int x = -1; x <= 0; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test5\n");
            }
            else if (i == 0 && j > 0 && j < n - 1)
            {
                for (int y = 0; y <= 1; y++)
                {
                    for (int x = -1; x <= 1; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test6\n");
            }
            else if (i == n - 1 && j > 0 && j < n - 1)
            {
                for (int y = -1; y <= 0; y++)
                {
                    for (int x = -1; x <= 1; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test7\n");
            }
            else if (j == 0 && i > 0 && i < n - 1)
            {
                for (int y = -1; y <= 1; y++)
                {
                    for (int x = 0; x <= 1; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test8\n");
            }
            else if (j == n - 1 && i > 0 && i < n - 1)
            {
                for (int y = -1; y <= 1; y++)
                {
                    for (int x = -1; x <= 0; x++)
                    {
                        sum += datain[(i * n + j) + (x + y * n)];
                    }
                }
                dataout[i * n + j] = round((float)sum / 9);
                // printf("test9\n");
            }
            else
            {
                dataout[i * n + j] = round((float)datain[i * n + j] / 9);
                // printf("test10\n");
            }
        }
    }
}
