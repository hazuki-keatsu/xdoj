#include <stdio.h>

int main()
{
    int n;
    int a[101];
    
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    int isMinHeap = 1;
    for (int i = 1; i * 2 <= n; i++) {
        if (a[i] > a[i * 2] || (i * 2 + 1 <= n && a[i] > a[i * 2 + 1])) {
            isMinHeap = 0;
            break;
        }
    }
    
    int isMaxHeap = 1;
    for (int i = 1; i * 2 <= n; i++) {
        if (a[i] < a[i * 2] || (i * 2 + 1 <= n && a[i] < a[i * 2 + 1])) {
            isMaxHeap = 0;
            break;
        }
    }
    
    if (isMinHeap) {
        printf("Min heap\n");
    } else if (isMaxHeap) {
        printf("Max heap\n");
    } else {
        printf("Not heap\n");
    }
    
    return 0;
}
