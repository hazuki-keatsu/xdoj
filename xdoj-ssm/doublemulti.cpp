#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* multiply(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len_result = len1 + len2;
    char* result = (char*)malloc(len_result + 1);
    memset(result, '0', len_result);
    result[len_result] = '\0';

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j;
            int p2 = i + j + 1;
            int sum = mul + (result[p2] - '0');

            result[p2] = (sum % 10) + '0';
            result[p1] += (sum / 10);
        }
    }

    for (int i = 0; i < len_result; i++) {
        if (result[i] != '0') {
            char* trimmed_result = strdup(result + i);
            free(result);
            return trimmed_result;
        }
    }

    char* zero_result = (char*)malloc(2);
    strcpy(zero_result, "0");
    free(result);
    return zero_result;
}

char* func(int n) {
    if (n == 1 || n == 0) {
        char* one = (char*)malloc(2);
        strcpy(one, "1");
        return one;
    } else {
        char* last = func(n - 1);
        char nch[12];
        sprintf(nch, "%d", n);

        char* result = multiply(last, nch);
        free(last);
        return result;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    char* result = func(n);
    printf("%s\n", result);
    free(result);

    return 0;
}