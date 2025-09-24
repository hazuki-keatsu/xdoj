#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *compress(char *src) {
    int len = strlen(src);
    char *compressed = (char *)malloc(101 * sizeof(char)); 
    if (!compressed) return src; 

    char *w = compressed;
    char *r = src;


    while (*r != '\0')
    {
        int count = 1;
        while (*r == *(r + 1))
        {
            count ++;
            r ++;
        }
        
        if (count > 2)
        {
            *w = *r;
            w++;
            itoa(count, w, 10);
            while (*w != '\0')
            {
                w++;
            }
            r++;
        }
        else
        {
            r -= (count - 1);
            for (int i = 0; i < count; i++)
            {
                *w = *r;
                w++;
                r++;
            }
        }
    }
    
    *w = '\0';

    return compressed; 
}

int main() {
    char src[100];
    scanf("%s", src);

    char *ps = compress(src);

    puts(ps);

    system("pause");
    return 0;
}