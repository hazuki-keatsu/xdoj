#include <stdio.h>
#include <stdlib.h>

#define SEATS 100

// 函数用于查找连续的空座位
int find_consecutive_empty_seats(int seats[], int p, int start) {
    for (int i = start; i < SEATS - p + 1; i++) {
        int j;
        for (j = i; j < i + p; j++) {
            if (seats[j] != 0) {
                break;
            }
        }
        if (j == i + p) {
            return i; // 找到了连续的空座位
        }
    }
    return -1; // 没有找到连续的空座位
}

// 函数用于分配座位
void allocate_seats(int n, int tickets[]) {
    int seats[SEATS] = {0}; // 初始化座位为未占用

    for (int i = 0; i < n; i++) {
        int p = tickets[i];
        int start = find_consecutive_empty_seats(seats, p, 0);
        
        if (start != -1) {
            // 如果找到了连续的空座位
            for (int j = start; j < start + p; j++) {
                seats[j] = 1; // 标记为已占用
            }
            printf("%d", start + 1);
            for (int j = start + 1; j < start + p; j++) {
                printf(" %d", j + 1);
            }
            printf("\n");
        } else {
            // 如果没有找到连续的空座位，分配不连续的座位
            for (int j = 0; j < p; j++) {
                int found = 0;
                for (int k = 0; k < SEATS; k++) {
                    if (seats[k] == 0) {
                        seats[k] = 1; // 标记为已占用
                        printf("%d ", k + 1);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    // 没有足够的座位
                    printf("Not enough seats\n");
                    return;
                }
            }
            printf("\n");
        }
    }
}

int main() {
    int n;
    scanf("%d", &n); // 读取购票指令的数量

    int tickets[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &tickets[i]); // 读取每个购票指令
    }

    allocate_seats(n, tickets); // 处理购票指令并输出结果

    return 0;
}