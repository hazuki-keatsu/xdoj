#include <stdio.h>

int main()
{
    int n, a[100] = {1, 1, 2};
    scanf("%d", &n);
    for (int i = 0; i < n - 3; i++)
    {
        a[i + 3] = a[i] + a[i + 2];
    }
    printf("%d", a[n - 1]);
}
