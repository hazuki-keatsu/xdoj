#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char num[21];
    int score;
    int mark;
} STU;

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    STU *stu = (STU *)calloc(m, sizeof(STU));

    for (int i = 0; i < m; i++)
    {
        scanf("%s %d %d", stu[i].num, &stu[i].score, &stu[i].mark);
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m - i - 1; j++)
        {
            if ((stu[j].score < stu[j+1].score)||
                (stu[j].score == stu[j+1].score && stu[j].mark < stu[j+1].mark)||
                (stu[j].score == stu[j+1].score && stu[j].mark == stu[j+1].mark && strcmp(stu[j].num, stu[j+1].num) > 0))
            {
                STU temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %d\n", stu[i].num, stu[i].score, stu[i].mark);
    }
    
    return 0;
}