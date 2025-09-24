#include <stdio.h>
#include <string.h>

typedef struct
{
    int num;
    int sum;
} TIM;

int main()
{
    int n;
    scanf("%d", &n);
    TIM tim[100] = {0};
    for (int i = 0; i < n; i++)
    {
        int in_h, in_m, out_h, out_m;
        scanf("%d %d:%d %d:%d", &tim[i].num, &in_h, &in_m, &out_h, &out_m);
        tim[i].sum = (out_h * 60 + out_m) - (in_h * 60 + in_m);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (tim[i].num == tim[j].num)
            {
                tim[i].sum += tim[j].sum;
                tim[j].num = 0;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tim[j].sum < tim[j + 1].sum || (tim[j].num > tim[j + 1].num && tim[j].sum == tim[j + 1].sum))
            {
                TIM temp = tim[j];
                tim[j] = tim[j + 1];
                tim[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (tim[i].num != 0 && tim[i].sum != 0)
        {
            printf("%d %d\n", tim[i].num, tim[i].sum);
        }
    }

    return 0;
}