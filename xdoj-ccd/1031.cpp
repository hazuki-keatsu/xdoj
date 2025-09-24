#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class Calculator
{
private:
    string expression;
    int result;

    // 应用运算符
    int applyOperation(int &a, int &b, char &opter)
    {
        if (opter == '+')
            return a + b;
        else if (opter == '-')
            return a - b;
        else if (opter == '*')
            return a * b;
        return 0;
    }

    // 是否是数字
    bool isDigit(char &ch)
    {
        if (ch - '0' >= 0 && ch - '0' <= 9)
        {
            return true;
        }
        return false;
    }

    // 是否是运算符
    bool isOps(char &ch)
    {
        if (ch == '+' || ch == '-' || ch == '*')
        {
            return true;
        }
        return false;
    }

    int priority(char &ch)
    {
        if (ch == '+' || ch == '-')
        {
            return 1;
        }
        else if (ch == '*')
        {
            return 2;
        }
        else 
        {
            return 0;
        }
    }

    void compute()
    {
        stack<int> numStack;
        stack<char> operatorStack;

        for (size_t i = 0; i < expression.length(); i++)
        {
            if (isDigit(expression[i]))
            {
                int val = 0;
                while (i < expression.length() && isDigit(expression[i]))
                {
                    val = (val * 10) + (expression[i] - '0');
                    i++;
                }
                numStack.push(val);
                i--;
            }
            else if (expression[i] == '(')
            {
                operatorStack.push(expression[i]);
            }
            else if (expression[i] == ')')
            {
                while (!operatorStack.empty() && operatorStack.top() != '(')
                {
                    if (numStack.size() < 2) {
                        return; // 防止栈下溢
                    }
                    int val2 = numStack.top();
                    numStack.pop();

                    int val1 = numStack.top();
                    numStack.pop();

                    if (operatorStack.empty()) {
                        return; // 防止运算符栈为空
                    }
                    char op = operatorStack.top();
                    operatorStack.pop();

                    numStack.push(applyOperation(val1, val2, op));
                }
                
                if (!operatorStack.empty())
                {
                    operatorStack.pop();
                }
            }
            else if (isOps(expression[i]))
            {
                while (!operatorStack.empty() && priority(operatorStack.top()) >= priority(expression[i]))
                {
                    int val2 = numStack.top();
                    numStack.pop();

                    int val1 = numStack.top();
                    numStack.pop();

                    char op = operatorStack.top();
                    operatorStack.pop();

                    numStack.push(applyOperation(val1, val2, op));
                }
                operatorStack.push(expression[i]);
            }
        }
        // 处理剩下的
        while (!operatorStack.empty())
        {
            int val2 = numStack.top();
            numStack.pop();

            int val1 = numStack.top();
            numStack.pop();

            char op = operatorStack.top();
            operatorStack.pop();

            numStack.push(applyOperation(val1, val2, op));
        }
        
        result = numStack.top();
    }

public:
    Calculator(string &expression) : expression(expression)
    {
        compute();
    }
    string Trevare()
    {
        return expression;
    }
    int getResult()
    {
        return result;
    }
};

int main()
{
    int count;
    vector<int> buffer;
    cin >> count;
    cin.ignore();
    for (int i = 0; i < count; i++)
    {
        string input;
        cin >> input;
        cin.ignore();
        Calculator cal(input);
        buffer.push_back(cal.getResult());
    }
    
    for(auto &element : buffer)
    {
        cout << element << endl;
    }

    return 0;
}