#include <iostream>
#include <string>
#include <stack>

bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '/' || ch == '*') {
        return true;
    }
    return false;
}

int main() {
    std::string str;
    std::cin >> str;

    std::stack<int> nums;
    for(auto ch : str) {
        if (isOperator(ch)) {
            if (nums.size() < 2) {
                return -1;
            } else {
                int num1 = nums.top();
                nums.pop();
                int num2 = nums.top();
                nums.pop();
                switch (ch)
                {
                case '+':
                    nums.push(num2 + num1);
                    break;
                case '-':
                    nums.push(num2 - num1);
                    break;
                case '*':
                    nums.push(num2 * num1);
                    break;
                case '/':
                    nums.push(num2 / num1);
                    break;
                }
            }
        } else {
            nums.push(ch - '0');
        }
    }

    if (!nums.empty()) {
        std::cout << nums.top() << std::endl;
    }

    return 0;
}