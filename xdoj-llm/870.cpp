#include <stdio.h>
#include <stdlib.h>

int partition(int a[], int left, int right);
void quicksort(int a[], int low, int high);

int partition(int a[], int left, int right)
{
    int pivot = a[left];
    int i = left;
    int j = right;
    
    while (i < j)
    {
        while (i < j && a[j] >= pivot)
            j--;
        if (i < j)
        {
            a[i] = a[j];
            i++;
        }
        
        while (i < j && a[i] < pivot)
            i++;
        if (i < j)
        {
            a[j] = a[i];
            j--;
        }
    }
    
    a[i] = pivot;
    return i;
}

int main()
{
    int n, a[1001];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    quicksort(a, 0, n - 1);
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}

void quicksort(int a[], int low, int high)
{
    if (low < high)
    {
        int k = partition(a, low, high);
        printf("%d ", k);
        quicksort(a, low, k - 1);
        quicksort(a, k + 1, high);
    }
}