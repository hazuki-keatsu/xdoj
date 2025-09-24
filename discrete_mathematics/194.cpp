#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

vector<string> split_to_vector(const string &str, const string &delimiter)
{
    vector<string> tokens;
    size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

class function_test
{
public:
    function_test(string &raw_d, string &raw_r, string &raw_f)
        : raw_d(raw_d), raw_r(raw_r), raw_f(raw_f)
    {
        preprocess();
        if (checkFunc())
        {
            if (isD() && isM())
            {
                cout << raw_d << " -> " << raw_r << ":s" << endl;
            }
            else if (isD() && !isM())
            {
                cout << raw_d << " -> " << raw_r << ":d" << endl;
            }
            else if (!isD() && isM())
            {
                cout << raw_d << " -> " << raw_r << ":m" << endl;
            }
            else
            {
                cout << raw_d << " -> " << raw_r << ":f" << endl;
            }
        }
        else
        {
            cout << raw_d << " -> " << raw_r << ":nf" << endl;
        }
    }

private:
    string raw_d;
    string raw_r;
    string raw_f;
    vector<string> domain;
    vector<string> range;
    vector<pair<string, string>> func;

    void preprocess()
    {
        string temp(raw_d);
        if (temp == "{}")  // 处理空集情况
        {
            domain.clear();
        }
        else
        {
            temp.erase(temp.begin());
            temp.pop_back();
            domain = split_to_vector(temp, ",");
        }

        temp = raw_r;
        if (temp == "{}")  // 处理空集情况
        {
            range.clear();
        }
        else
        {
            temp.erase(temp.begin());
            temp.pop_back();
            range = split_to_vector(temp, ",");
        }

        temp = raw_f;
        if (temp == "{}")  // 处理空函数情况
        {
            func.clear();
        }
        else
        {
            temp.erase(temp.begin());
            temp.pop_back();
            temp.erase(temp.begin());
            temp.pop_back();
            vector<string> buffer = split_to_vector(temp, ">,<");
            for (auto &i : buffer)
            {
                vector<string> ii = split_to_vector(i, ",");
                func.push_back({ii[0], ii[1]});
            }
        }
    }

    bool checkFunc()
    {
        // 特殊情况：空集作为定义域
        if (domain.empty() && func.empty()) {
            return true;
        }
        if (domain.empty() && !func.empty()) {
            return false;
        }

        // 检查函数关系的有效性
        for (auto &i : func)
        {
            // 检查定义域
            if (std::find(domain.begin(), domain.end(), i.first) == domain.end())
                return false;
            // 检查值域
            if (std::find(range.begin(), range.end(), i.second) == range.end())
                return false;
        }

        // 检查每个定义域元素只对应一个值
        set<string> domain_elements;
        for (auto &i : func)
        {
            if (!domain_elements.insert(i.first).second)
                return false;
        }

        // 检查定义域中的每个元素都被映射
        set<string> all_domain(domain.begin(), domain.end());
        return domain_elements == all_domain;
    }

    bool isD()
    {
        set<string> range_elements;
        for (auto &i : func)
        {
            if (!range_elements.insert(i.second).second)
                return false;
        }
        return true;
    }

    bool isM()
    {
        bool is = false;
        set<string> in;
        set<string> comp(range.begin(), range.end());
        for (auto &i : func)
        {
            in.insert(i.second);
        }

        if (in == comp)
        {
            is = true;
        }
        return is;
    }
};

int main()
{
    string domain, range, func;
    cin >> domain >> range >> func;
    function_test ft(domain, range, func);
    return 0;
}