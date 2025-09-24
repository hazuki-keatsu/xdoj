#include <stdio.h>
#include <string.h>

typedef struct
{
    int yyyy;
    int mm;
    int dd;
    int size;
} FI;

void sort(FI *file, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (file[j].yyyy < file[j + 1].yyyy ||
                (file[j].yyyy == file[j + 1].yyyy && file[j].mm < file[j + 1].mm) ||
                (file[j].yyyy == file[j + 1].yyyy && file[j].mm == file[j + 1].mm && file[j].dd < file[j + 1].dd) ||
                (file[j].yyyy == file[j + 1].yyyy && file[j].mm == file[j + 1].mm && file[j].dd == file[j + 1].dd && file[j].size < file[j + 1].size))
            {
                FI temp = file[j];
                file[j] = file[j + 1];
                file[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    FI file[100];
    memset(file, 0, 100 * sizeof(FI));
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d/%d/%d %d", &file[i].yyyy, &file[i].mm, &file[i].dd, &file[i].size);
    }

    sort(file, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d/%d/%d %d\n", file[i].yyyy, file[i].mm, file[i].dd, file[i].size);
    }

    return 0;
}