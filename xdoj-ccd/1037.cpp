#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;

class wordSumUP
{
public:
    wordSumUP(string input) : str(input)
    {
        allToLower();
        sumup();
    }
    void printStr()
    {
        cout << str << endl;
    }
    void printResult()
    {
        cout << result.size() << endl;
        for (auto pos = result.begin(); pos != result.end(); pos++)
        {
            cout << pos->first << " " << pos->second << endl;
        }
    }

private:
    string str;
    map<string, int> result;
    void allToLower()
    {
        for (auto word = str.begin(); word != str.end(); word++)
        {
            *word = tolower(*word);
        }
    }
    void addWord(const string &word)
    {
        auto it = result.find(word);
        if (it != result.end())
        {
            it->second++;
        }
        else
        {
            result.insert({word, 1});
        }
    }
    void handleAbbreviation(const string &abbr)
    {
        if (abbr == "s")
        {
            addWord("is");
        }
        else if (abbr == "m")
        {
            addWord("am");
        }
        else if (abbr == "re")
        {
            addWord("are");
        }
        else
            ;
    }
    void sumup()
    {
        auto pos = str.begin();
        string buffer;
        while (pos != str.end())
        {
            // 跳过空字符
            while (pos != str.end() && !isalpha(*pos))
            {
                ++pos;
            }
            if (pos == str.end())
                break;

            // 获取单词
            buffer.clear();
            while (pos != str.end() && isalpha(*pos))
            {
                buffer.push_back(*pos);
                ++pos;
            }

            // 只统计非空单词
            if (!buffer.empty())
            {
                addWord(buffer);
            }

            // 统计缩写
            buffer.clear();
            if (pos != str.end() && *pos == '\'')
            {
                pos++;
                while (pos != str.end() && isalpha(*pos))
                {
                    buffer.push_back(*pos);
                    ++pos;
                }
            }

            if (!buffer.empty())
            {
                handleAbbreviation(buffer);
            }
        }
    }
};

int main()
{
    string input;
    while (true)
    {
        string buffer;
        getline(cin, buffer);

        size_t pos = buffer.find('#');
        if (pos != string::npos)
        {
            input += buffer.substr(0, pos);
            break;
        }
        else
        {
            input += buffer + '\n';
        }
    }

    if (!input.empty() && input.back() == '\n')
    {
        input.pop_back();
    }

    wordSumUP wsu(input);

    // wsu.printStr();
    wsu.printResult();
    return 0;
}