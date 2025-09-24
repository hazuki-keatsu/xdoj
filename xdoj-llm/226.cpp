#include <iostream>
#include <string>
using namespace std;

void swapChar(string &s, const int &i, const int &j)
{
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

int main()
{
    string str;

    cin >> str;

    for (int i = str.length(); i >= 0; i--) {
        for (int i = 0; i < str.length() - 1; i++)
        {
            if (str[i] > str[i + 1])
            {
                swapChar(str, i, i + 1);
            }
        }
    }

    cout << str;

    return 0;
}