#include <stdio.h>
int biSearch(int n, int a[], int key)
{
    if (n <= 0) return -1;
    int front = 0;
    int end = n - 1;
    while (front <= end) {
        int mid = front + (end - front) / 2;
        printf("%d ", a[mid]);
        if (a[mid] == key) {
            return mid;
        } else if (a[mid] > key) {
            end = mid - 1;
        } else {
            front = mid + 1;
        }
    }
    return -1;
}
int main()
{
    int i, n, key;
    int a[101];
    scanf("%d%d", &n, &key);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int position = biSearch(n, a, key);
    if (-1 == position)
        printf("[Not found]\n");
    else
        printf("[Found at index %d]\n", position);
    return 0;
}