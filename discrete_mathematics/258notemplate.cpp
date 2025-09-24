#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

// 处理set类型
set<string> split_set(const string &str, const string &delimiter) {
    set<string> tokens;
    size_t start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != string::npos) {
        tokens.insert(str.substr(start, end - start));
        start = end + delimiter.length();
    }
    if (!str.substr(start).empty()) {
        tokens.insert(str.substr(start));
    }
    return tokens;
}

// 处理vector类型
vector<string> split_vector(const string &str, const string &delimiter) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }
    if (!str.substr(start).empty()) {
        tokens.push_back(str.substr(start));
    }
    return tokens;
}

// 处理pair类型
pair<string, string> split_pair(const string &str, const string &delimiter) {
    pair<string, string> tokens;
    size_t delimiter_pos = str.find(delimiter);
    if (delimiter_pos != string::npos) {
        tokens.first = str.substr(0, delimiter_pos);
        tokens.second = str.substr(delimiter_pos + delimiter.length());
    } else {
        tokens.first = str;
        tokens.second = "";
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

        s = split_set(buffer, ",");

        buffer = raw_relation;
        buffer.erase(buffer.begin());
        buffer.erase(buffer.begin());
        buffer.pop_back();
        buffer.pop_back();

        vector<string> mid = split_vector(buffer, ">,<");

        for (auto &i : mid)
        {
            pair<string, string> temp = split_pair(i, ",");
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