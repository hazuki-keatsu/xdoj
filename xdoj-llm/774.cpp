#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cctype>

int getPriority(char op)
{
    int priority;
    switch (op)
    {
    case '+':
        priority = 1;
        break;
    case '-':
        priority = 1;
        break;
    case '*':
        priority = 2;
        break;
    case '/':
        priority = 2;
        break;
    case '(':
        priority = 0;
        break;
    default:
        priority = 0;
        break;
    }
    return priority;
}

bool isOp(char ch) {
    if (ch == '+' || ch == '-' || ch == '/' || ch == '*') {
        return true;
    }
    return false;
}

int main() {
    std::stack<char> sOp;
    std::vector<std::string> output;

    std::string line;
    if (!std::getline(std::cin, line)) return 0; // 无输入
    if (line.empty()) {
        if (!std::getline(std::cin, line)) return 0;
    }

    // 去掉空格，得到纯表达式字符串
    std::string expr;
    expr.reserve(line.size());
    for (char c : line) {
        if (!std::isspace(static_cast<unsigned char>(c))) expr.push_back(c);
    }

    for (size_t i = 0; i < expr.size(); ) {
        char ch = expr[i];
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            std::string num;
            while (i < expr.size() && std::isdigit(static_cast<unsigned char>(expr[i]))) {
                num.push_back(expr[i]);
                ++i;
            }
            output.push_back(num);
            continue;
        } else if (ch == '(') {
            sOp.push(ch);
        } else if (ch == ')') {
            while (!sOp.empty() && sOp.top() != '(') {
                output.emplace_back(1, sOp.top());
                sOp.pop();
            }
            if (!sOp.empty() && sOp.top() == '(') sOp.pop();
        } else if (isOp(ch)) {
            while (!sOp.empty() && getPriority(sOp.top()) >= getPriority(ch)) {
                output.emplace_back(1, sOp.top());
                sOp.pop();
            }
            sOp.push(ch);
        } else {
        }
        ++i;
    }

    // 弹出剩余运算符
    while (!sOp.empty()) {
        if (sOp.top() == '(') {
            sOp.pop();
            continue;
        }
        output.emplace_back(1, sOp.top());
        sOp.pop();
    }

    // 输出结果
    if (output.empty()) {
        return 0;
    }
    for (size_t i = 0; i < output.size(); ++i) {
        std::cout << output[i];
        if (i + 1 < output.size()) std::cout << ' ';
    }
    std::cout << '\n';
    return 0;
}