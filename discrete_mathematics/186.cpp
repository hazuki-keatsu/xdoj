#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

// 字符串分割函数
set<string> split(const string &str, const string &delimiter)
{
    set<string> tokens;
    size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != string::npos)
    {
        tokens.insert(str.substr(start, end - start));
        start = end + delimiter.length();
    }

    tokens.insert(str.substr(start));

    return tokens;
}

// 等价关系类
class Equality
{
public:
    Equality(const string &input, int &count) : raw_string(input), count(count)
    {
        // 处理空集
        if (count == 0)
        {
            cout << "{}";
            return;
        }

        // 字符串处理
        raw_string.erase(raw_string.begin());
        raw_string.pop_back();
        s = split(raw_string, ",");
        // 初始化相等关系
        initReflexive();
        // 初始化对称关系元
        initSymmetric();

        // 插入对称关系元
        int total_way = 1 << symmetric_v.size();
        for (int i = 0; i < total_way; i++)
        {
            set<pair<string, string>> buffer(reflexive_s);
            for (int j = 0; j < symmetric_v.size(); j++)
            {
                if ((i >> j) & 1)
                {
                    buffer.insert(symmetric_v[j]);
                    auto temp = symmetric_v[j];
                    swap(temp.first, temp.second);
                    buffer.insert(temp);
                }
            }
            // 进行传递闭包运算
            transitiveClosure(buffer);

            // 字符串拼接
            stringstream ss;
            ss << "{";
            bool first = true;
            for (const auto &pair : buffer)
            {
                if (!first)
                {
                    ss << ",";
                }
                ss << "<" << pair.first << "," << pair.second << ">";
                first = false;
            }
            ss << "}" << endl;

            // 字符串进入set进行排列
            output.insert(ss.str());
        }
    }

    // 遍历输入元素（测试用）
    void set_traverse()
    {
        for (auto &i : s)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    // 输出所有的字符串
    void output_print()
    {
        vector<string> sorted_output(output.begin(), output.end());

        // 短的先出
        sort(sorted_output.begin(), sorted_output.end(), [](const string &a, const string &b)
            {
                return a.length() < b.length();
            });

        for (const auto &str : sorted_output)
        {
            cout << str;
        }
    }

private:
    string raw_string;
    int count;
    set<string> s;
    set<pair<string, string>> reflexive_s;
    vector<pair<string, string>> symmetric_v;
    set<string> output;

    void initReflexive()
    {
        // 求解相等关系
        for (auto &i : s)
        {
            pair<string, string> buffer;
            buffer.first = i;
            buffer.second = i;
            reflexive_s.insert(buffer);
        }

        stringstream ss;
        ss << "{";
        bool first = true;
        for (const auto &pair : reflexive_s)
        {
            if (!first)
            {
                ss << ",";
            }
            ss << "<" << pair.first << "," << pair.second << ">";
            first = false;
        }
        ss << "}" << endl;

        output.insert(ss.str());
    }

    void initSymmetric()
    {
        // 求解对称关系元
        for (auto &i : s)
        {
            for (auto &j : s)
            {
                pair<string, string> buffer;
                if (i != j && (std::find(symmetric_v.begin(), symmetric_v.end(), make_pair(j, i)) == symmetric_v.end()))
                {
                    buffer.first = i;
                    buffer.second = j;
                    symmetric_v.push_back(buffer);
                }
            }
        }
    }

    // 传递闭包
    void transitiveClosure(set<pair<string, string>> &noClosure)
    {
        bool newPairsInserted = true;
        while (newPairsInserted)
        {
            newPairsInserted = false;
            set<pair<string, string>> newPairs;

            for (auto &element : noClosure)
            {
                for (auto &buffer : noClosure)
                {
                    if (element.second == buffer.first)
                    {
                        pair<string, string> temp({element.first, buffer.second});
                        if (noClosure.find(temp) == noClosure.end())
                        {
                            newPairs.insert(temp);
                            newPairsInserted = true;
                        }
                    }
                }
            }

            for (auto &newPair : newPairs)
            {
                noClosure.insert(newPair);
            }
        }
    }
};

int main()
{
    int count;
    string input;
    cin >> count >> input;
    Equality eq(input, count);
    // eq.set_traverse();
    eq.output_print();

    return 0;
}