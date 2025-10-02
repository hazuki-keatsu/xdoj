#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
int main()
{
    std::string str;
    std::getline(std::cin, str);
    std::stringstream buffer;
    std::stack<std::string> tokens;

    // tokenization
    for (char ch : str)
    {
        if (ch != ' ')
        {
            buffer << ch;
        }
        else
        {
            std::string temp;
            buffer >> temp;
            tokens.push(temp);
            buffer.str("");
            buffer.clear();
        }
    }
    std::string temp;
    buffer >> temp;
    tokens.push(temp);
    buffer.str("");
    buffer.clear();

    std::stack<char> ops;
    std::stack<int> nums;
    bool flag = false;
    while (!tokens.empty())
    {
        std::string i = tokens.top();
        tokens.pop();
        if (i == "+" || i == "-" || i == "*" || i == "/")
        {
            int num1 = nums.top();
            nums.pop();
            int num2 = nums.top();
            nums.pop();

            switch (*i.c_str())
            {
            case '+':
                nums.push(num1 + num2);
                break;
            case '-':
                nums.push(num1 - num2);
                break;
            case '*':
                nums.push(num1 * num2);
                break;
            case '/':
                nums.push(num1 / num2);
                break;
            }
        }
        else
        {
            nums.push(atoi(i.c_str()));
        }
    }

    if (!nums.empty()) {
        std::cout << nums.top() << std::endl;
    }

    return 0;
}