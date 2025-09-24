#include <stdio.h>

int axis[1281][1025] = {0}; // 全局变量

int main()
{
    int n, m, vecsta[10][2] = {0}, vecend[10][2] = {0};
    int click[50][2] = {0};
    scanf("%d %d", &n, &m);
    // 最下层到最顶层
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d", &vecsta[i][0], &vecsta[i][1], &vecend[i][0], &vecend[i][1]);
        // 写入窗口信息
        for (int x = vecsta[i][0]; x <= vecend[i][0]; x++)
        {
            for (int y = vecsta[i][1]; y <= vecend[i][1]; y++)
            {
                axis[x][y] = i + 1;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &click[i][0], &click[i][1]);
    }

    for (int i = 0; i < m; i++)
    {
        int num = axis[click[i][0]][click[i][1]];

        if (num == 0)
        {
            printf("IGNORED\n");
        }
        else
        {
            printf("%d\n", num);
            // 刷新窗口
            for (int x = vecsta[num - 1][0]; x <= vecend[num - 1][0]; x++)
            {
                for (int y = vecsta[num - 1][1]; y <= vecend[num - 1][1]; y++)
                {
                    axis[x][y] = num;
                }
            }
        }
    }

    return 0;
}