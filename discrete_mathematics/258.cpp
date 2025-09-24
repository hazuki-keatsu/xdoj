#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

// 一劳永逸的模板函数，支持set,vector,stack,queue,pair
template <typename Container>
Container split(const string &str, const string &delimiter)
{
    Container tokens;
    size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != string::npos)
    {
        if constexpr (std::is_same_v<Container, set<string>> ||
                      std::is_same_v<Container, vector<string>>)
        {
            tokens.insert(tokens.end(), str.substr(start, end - start));
        }
        else if constexpr (std::is_same_v<Container, stack<string>>)
        {
            tokens.push(str.substr(start, end - start));
        }
        else if constexpr (std::is_same_v<Container, queue<string>>)
        {
            tokens.push(str.substr(start, end - start));
        }
        else if constexpr (std::is_same_v<Container, pair<string, string>>)
        {
            size_t delimiter_pos = str.find(delimiter, start);
            if (delimiter_pos != string::npos)
            {
                tokens.first = str.substr(start, delimiter_pos - start);
                tokens.second = str.substr(delimiter_pos + delimiter.length());
            }
            else
            {
                tokens.first = str.substr(start);
                tokens.second = "";
            }
            return tokens;
        }
        start = end + delimiter.length();
    }

    if (!str.substr(start).empty())
    {
        if constexpr (std::is_same_v<Container, set<string>> ||
                      std::is_same_v<Container, vector<string>>)
        {
            tokens.insert(tokens.end(), str.substr(start));
        }
        else if constexpr (std::is_same_v<Container, stack<string>>)
        {
            tokens.push(str.substr(start));
        }
        else if constexpr (std::is_same_v<Container, queue<string>>)
        {
            tokens.push(str.substr(start));
        }
        else if constexpr (std::is_same_v<Container, pair<string, string>>)
        {
            tokens.first = str.substr(start);
            tokens.second = "";
        }
    }

    return tokens;
}

class equality_relation
{
public:
    equality_relation(const string &input, const string &relation)
        : raw_elements(input), raw_relation(relation)
    {
        preprocess();
        execute();
    }

    void traverse_s()
    {
        for (auto &i : s)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    void traverse_r()
    {
        for (auto &i : r)
        {
            cout << "<" << i.first << "," << i.second << ">" << " ";
        }
        cout << endl;
    }

    bool getResult()
    {
        return result;
    }

private:
    string raw_elements;
    string raw_relation;
    set<string> s;
    set<pair<string, string>> r;
    bool result;

    void preprocess()
    {
        string buffer(raw_elements);
        buffer.erase(buffer.begin());
        buffer.pop_back();

        s = split<set<string>>(buffer, ",");

        buffer = raw_relation;
        buffer.erase(buffer.begin());
        buffer.erase(buffer.begin());
        buffer.pop_back();
        buffer.pop_back();

        vector<string> mid = split<vector<string>>(buffer, ">,<");

        for (auto &i : mid)
        {
            pair<string, string> temp = split<pair<string, string>>(i, ",");
            r.insert(temp);
        }
    }

    void execute()
    {
        bool isEquality = true;

        // 是否在A上
        for (auto &element : r)
        {
            if (s.find(element.first) == s.end() || s.find(element.second) == s.end())
            {
                isEquality = false;
            }
        }

        // 自反性
        for (auto &element : s)
        {
            if (r.find(make_pair(element, element)) == r.end())
            {
                isEquality = false;
            }
        }

        // 对称性
        for (auto &element : r)
        {
            pair<string, string> temp(element);
            swap(temp.first, temp.second);
            if (r.find(temp) == r.end())
            {
                isEquality = false;
            }
        }

        // 传递性
        for (auto &i : r)
        {
            for (auto &j : r)
            {
                if (i.second == j.first)
                {
                    if (r.find(make_pair(i.first, j.second)) == r.end())
                    {
                        isEquality = false;
                    }
                }
            }
        }
        result = isEquality;
    }
};

int main()
{
    string set, relation;
    cin >> set >> relation;
    equality_relation er(set, relation);
    // er.traverse_s();
    // er.traverse_r();

    cout << (er.getResult() == true ? "Yes" : "No") << endl;
    return 0;
}