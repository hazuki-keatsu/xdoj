#include <stdio.h>

void generateNextPermutation(int arr[], int n) {
    int i = n - 1;
    while (i > 0 && arr[i-1] >= arr[i]) {
        i--;
    }
    
    if (i > 0) {
        int j = n - 1;
        while (arr[j] <= arr[i-1]) {
            j--;
        }
        
        int temp = arr[i-1];
        arr[i-1] = arr[j];
        arr[j] = temp;
    }

    
    int left = i, right = n - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

void printPermutation(int arr[], int n, int isLast) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }
    if (!isLast) printf("\n");
}

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    if (n < 2 || n >= 10) {
        return 1;
    }
    
    int arr[10];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    int total = factorial(n);
    for (int i = 1; i <= total; i++) {
        printPermutation(arr, n, i == total);
        if (i < total) {
            generateNextPermutation(arr, n);
        }
    }
    
    return 0;
}