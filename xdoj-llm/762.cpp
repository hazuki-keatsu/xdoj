#include <iostream>
#include <string>
#include <stack>

bool epoch(std::string str);

int main() {
    size_t count;
    std::cin >> count;
    bool *results = new bool[count];
    for (size_t i = 0; i < count; i ++) {
        std::string temp;
        std::cin >> temp;
        if (epoch(temp)) {
            results[i] = true;
        } else {
            results[i] = false;
        }
    }

    for (size_t i = 0; i < count; i++) {
        std::cout << (results[i] == true ? "Yes" : "No") << std::endl;
    }

    delete results;
    return 0;
}

bool epoch(std::string str) {
    std::stack<char> buffer;

    for (auto s : str) {
        if (s == '(' || s == '[') {
            buffer.push(s);
        }
        else if (s == ')' || s == ']') {
            if (buffer.empty()) {
                return false; 
            }
            char top = buffer.top();
            if ((s == ')' && top == '(') || 
                (s == ']' && top == '[')) {
                buffer.pop(); 
            } else {
                return false; 
            }
        }
    }

    return buffer.empty();
}