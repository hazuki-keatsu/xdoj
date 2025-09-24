// #include <stdio.h>
// #include <string.h>

// int main(){
//     char chin[101], chout[200];
//     memset(chin, 0, 101 * sizeof(char));
//     fgets(chin, 101, stdin);
//     int len = strlen(chin) - 1;
//     chin[len] = '\0';

//     for (int i = 0; i < len; i++)
//     {
//         chout[2 * i] = chin[i];
//         chout[2 * i + 1] = ' ';
//     }
//     chout[2 * len] = '\0';
    
//     puts(chout);
//     return 0;
// }

// NB

// #include <iostream>

// using namespace std;

// int main(){
//     string s;
//     cin >> s;
//     for (int i = 0; i < s.size(); i++)
//     {
//         cout << s[i] << ' ';
//     }
//     return 0;
// }

#include <iostream>
#include <string.h>

using namespace std;

int main(){
    char s[100];
    cin >> s;
    for (int i = 0; i < strlen(s); i++)
    {
        cout << s[i] << ' ';
    }
    return 0;
}