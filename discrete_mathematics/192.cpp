#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <cctype>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

// 扩展枚举以包含括号
enum lc
{
    LNOT,
    TO,
    LEFTRIGHT,
    LAND,
    LOR,
    LEFT_PAREN,
    RIGHT_PAREN
};

// 定义运算符优先级
map<lc, int> precedence = {
    {LNOT, 3},
    {LAND, 2},
    {LOR, 2},
    {TO, 1},
    {LEFTRIGHT, 1},
    {LEFT_PAREN, 0},
    {RIGHT_PAREN, 0}};

class proposition
{
public:
    proposition(const string &input, const string &split) : raw_input(input), delimeter(split)
    {
        preprocess();
    }

    // 输出真值表
    void print_truth_table()
    {
        // 收集所有不同的命题变量
        set<string> variables;
        stack<string> temp = pro_variable;
        while (!temp.empty())
        {
            string token = temp.top();
            if (isalpha(token[0]))
            {
                variables.insert(token);
            }
            temp.pop();
        }

        vector<string> vars(variables.begin(), variables.end());
        sort(vars.begin(), vars.end());
        int n = vars.size();
        int rows = 1 << n;

        // 打印表头
        for (const string &var : vars)
        {
            cout << var << " ";
        }
        cout << raw_input << endl;

        // 生成并计算所有可能的真值组合
        for (int i = 0; i < rows; i++)
        {
            map<string, bool> values;
            for (int j = 0; j < n; j++)
            {
                values[vars[j]] = (i & (1 << (n - j - 1))) != 0;
                cout << values[vars[j]] << " ";
            }
            cout << evaluate(values) << endl;
        }
    }

private:
    string raw_input;
    stack<string> pro_variable; // 存储后缀表达式
    stack<lc> operators;        // 用于处理运算符
    size_t i;
    string delimeter;

    // 将中缀表达式转换为后缀表达式
    void preprocess()
    {
        string token;
        for (i = 0; i < raw_input.length(); i++)
        {
            char c = raw_input[i];

            if (isalpha(c)) // 处理命题变量
            {
                token = "";
                while (i < raw_input.length() && isalnum(raw_input[i]))
                {
                    token += raw_input[i++];
                }
                i--;
                pro_variable.push(token);
            }
            else if (c == '(')
            {
                operators.push(LEFT_PAREN);
            }
            else if (c == ')')
            {
                // 处理右括号，将括号内的所有运算符弹出
                while (!operators.empty() && operators.top() != LEFT_PAREN)
                {
                    process_operator(operators.top());
                    operators.pop();
                }
                if (!operators.empty())
                {
                    operators.pop(); // 弹出左括号
                }
            }
            else if (is_operator(c))
            {
                lc current_op = char_to_operator(c);
                // 修改运算符优先级处理
                while (!operators.empty() &&
                       operators.top() != LEFT_PAREN &&
                       (precedence[operators.top()] > precedence[current_op] ||
                        (precedence[operators.top()] == precedence[current_op] &&
                         current_op != LNOT)))
                {
                    process_operator(operators.top());
                    operators.pop();
                }
                operators.push(current_op);
            }
        }

        // 处理剩余的运算符
        while (!operators.empty())
        {
            process_operator(operators.top());
            operators.pop();
        }

        // 反转后缀表达式
        stack<string> temp;
        while (!pro_variable.empty())
        {
            temp.push(pro_variable.top());
            pro_variable.pop();
        }
        pro_variable = temp;
    }

    bool is_operator(char c)
    {
        return c == '~' || c == '-' || c == '<' || c == '\\' || c == '/';
    }

    lc char_to_operator(char c)
    {
        switch (c)
        {
        case '~':
            return LNOT;
        case '/':
            if (i + 1 < raw_input.length() && raw_input[i + 1] == '\\')
            {
                i++;         // 跳过下一个字符
                return LAND; // 合取
            }
            break;
        case '\\':
            if (i + 1 < raw_input.length() && raw_input[i + 1] == '/')
            {
                i++;        // 跳过下一个字符
                return LOR; // 析取
            }
            break;
        case '-':
            if (i + 1 < raw_input.length() && raw_input[i + 1] == '>')
            {
                i++;       // 跳过下一个字符
                return TO; // 蕴涵
            }
            break;
        case '<':
            if (i + 2 < raw_input.length() &&
                raw_input[i + 1] == '-' &&
                raw_input[i + 2] == '>')
            {
                i += 2;           // 跳过后面两个字符
                return LEFTRIGHT; // 等价
            }
            break;
        }
        return LEFT_PAREN; // 默认返回
    }

    void process_operator(lc op)
    {
        // 将运算符转换为字符串形式存储在后缀表达式中
        switch (op)
        {
        case LNOT:
            pro_variable.push("~");
            break;
        case LAND:
            pro_variable.push("/\\");
            break;
        case LOR:
            pro_variable.push("\\/");
            break;
        case TO:
            pro_variable.push("->");
            break;
        case LEFTRIGHT:
            pro_variable.push("<->");
            break;
        default:
            break;
        }
    }

    // 计算后缀表达式的值
    bool evaluate(const map<string, bool> &values)
    {
        stack<bool> result;

        for (stack<string> temp = pro_variable; !temp.empty(); temp.pop())
        {
            string token = temp.top();

            if (isalpha(token[0]))
            {
                result.push(values.at(token));
            }
            else if (token == "~")
            {
                if (result.empty())
                    continue;
                bool val = result.top();
                result.pop();
                result.push(!val);
            }
            else
            {
                if (result.size() < 2)
                    continue;
                bool b = result.top();
                result.pop();
                bool a = result.top();
                result.pop();

                if (token == "/\\")
                    result.push(a && b);
                else if (token == "\\/")
                    result.push(a || b);
                else if (token == "->")
                    result.push(!a || b);
                else if (token == "<->")
                    result.push(a == b);
            }
        }
        return result.empty() ? false : result.top();
    }
};

int main()
{
    string input;
    cin >> input;
    proposition prop(input, " ");
    prop.print_truth_table();
    return 0;
}