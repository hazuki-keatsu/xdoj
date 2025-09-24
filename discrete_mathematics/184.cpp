#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

// 字符串分割函数
vector<string> split(const string &str, const string &delimiter)
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

// 集合类
class Set
{
public:
    Set(string input)
    {        // 处理空集的情况
        if (input == "{}")
        {
            set.clear();
            rela.clear();
            rho.clear();
            return;
        }

        // 分割字符
        string temp = input.substr(1, input.length() - 2);
        set = split(temp, ",");

        // 清空rela
        rela.clear();
        rela.shrink_to_fit();
        // 初始化rela
        rela = relative();

        // 初始化幂集
        rho = rho_relative(rela);
    }

    // vector遍历函数
    void traverse()
    {
        cout << "Input elements:\n";
        for (size_t i = 0; i < set.size(); i++)
        {
            cout << set[i] << " ";
        }
        cout << endl;
    }

    // 打印vector的二元关系
    void relative_print()
    {
        cout << "Birelative:\n";
        for (size_t i = 0; i < rela.size(); i++)
        {
            cout << "{<" << rela[i].first << "," << rela[i].second << ">},";
        }
        cout << endl;
        return;
    }

    void rhoset_print()
    {
        // cout << "All subsets of rhoset:\n";
        if (rho.empty())
        {
            cout << "{}" << endl;
            return;
        }
        
        for (const auto &subset : rho)
        {
            cout << "{";
            for (size_t i = 0; i < subset.size(); i++)
            {
                cout << "<" << subset[i].first << "," << subset[i].second << ">";
                if (i != subset.size() - 1)
                {
                    cout << ",";
                }
            }
            cout << "}" << endl;
        }
        cout << endl;
        return;
    }

private:
    vector<string> set;
    vector<pair<string, string>> rela;
    vector<vector<pair<string, string>>> rho;

    // 关系初始化函数
    vector<pair<string, string>> relative()
    {
        vector<pair<string, string>> re;
        for (size_t i = 0; i < set.size(); i++)
        {
            for (size_t j = 0; j < set.size(); j++)
            {
                pair<string, string> temp;
                temp = {set[i], set[j]};
                re.push_back(temp);
            }
        }
        return re;
    }

    // 集合关系遍历
    vector<vector<pair<string, string>>> rho_relative(vector<pair<string, string>> re)
    {
        vector<vector<pair<string, string>>> rho_set;
        int total_subsets = 1 << re.size();

        for (size_t i = 0; i < total_subsets; i++)
        {
            vector<pair<string, string>> subset;
            for (size_t j = 0; j < re.size(); j++)
            {
                if ((i >> j) & 1)
                {
                    subset.push_back(re[j]);
                }
            }
            rho_set.push_back(subset);
        }

        // 对 rho_set 进行排序
        sort(rho_set.begin(), rho_set.end(), [](const vector<pair<string, string>> &a, const vector<pair<string, string>> &b)
             {
                 if (a.size() != b.size())
                 {
                     return a.size() < b.size(); // 按元素个数排序
                 }
                 return a < b; // 按字典序排序
             });

        return rho_set;
    }
};

// 主调函数
int main()
{
    string input;
    int count;
    cin >> count >> input;
    Set s(input);
    // s.traverse();
    // s.relative_print();
    s.rhoset_print();

    return 0;
}