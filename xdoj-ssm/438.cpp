#include <stdio.h>
#include <math.h>

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    short a[100][100] = {0}, b[100][100] = {0};
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%hd", &a[i][j]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%hd", &b[i][j]);
        }
    }

    int count = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == b[i][j])
            {
                count++;
            }     
        }
    }
    
    float result = round((float)count / (m * n) * 10000) / 100;
    printf("%.2f\n", result);
    
    return 0;
}