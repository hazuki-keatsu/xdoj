#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char input[1000000] = {0};
    fgets(input, 1000000, stdin);
    input[strlen(input) - 1] = '\0';

    // to get n * m
    int n = 0, m = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '[')
        {
            n++;
        }
    }
    n--;

    for (int i = 1; input[i] != ']'; i++)
    {
        if (input[i] == ',')
        {
            m++;
        }
    }
    m++;

    // to create a matrix
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL)
    {
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(m * sizeof(int));

        if (matrix[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            exit(1);
        }
    }

    int k = 0, i = 0 ;
    while (input[i] != '\0')
    {
        if (isdigit(input[i]) == 1)
        {
            int q = 0;
            char buffer[3] = {0};
            while (isdigit(input[i]) == 1)
            {
                buffer[q] = input[i];
                q++;
                i++;
            }
            matrix[k / m][k % m] = atoi(buffer);
            k++;
        }

        i++;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            else if (i == 0 && j != 0)
            {
                matrix[i][j] += matrix[i][j - 1];
            }
            else if (i != 0 && j == 0)
            {
                matrix[i][j] += matrix[i - 1][j];
            }
            else
            {
                matrix[i][j] += (matrix[i - 1][j] > matrix[i][j - 1]) ? matrix[i][j - 1] : matrix[i - 1][j];
            }
        }
    }
    
    printf("%d\n", matrix[n - 1][m - 1]);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}