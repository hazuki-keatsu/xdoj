#include <iostream>
#include <string>

int main () {
    std::string s;
    std::cin >> s;

    size_t len = s.length();
    bool flag;

    for (int i = 1; i <= len; i++) {
        if (len % i == 0) {
            flag = true;
            for (int j = i; j < len; j++) {
                if (s[j]!=s[j%i]) {
                    flag = false;
                    break;
                }
            }
            if(flag == true) {
                std::cout << i;
                break;
            }
        }
    }

    return 0;
}