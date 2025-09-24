#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

set<string> split_to_set(const string &str, const string &delimiter)
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

class relations
{
public:
    relations(const string &input, size_t &count) : raw_input(input), count(count)
    {
        string temp(raw_input);
        temp.pop_back();
        temp.erase(temp.begin());

        s = split_to_set(temp, ",");
        init_relations();
    }

    void traverse_s()
    {
        for (auto &i : s)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    void traverse_all_relations()
    {
        for (auto &i : all_relations)
        {
            cout << "<" << i.first << "," << i.second << ">" << " ";
        }
        cout << endl;
    }

    void print_reflexive()
    {
        if (count == 0)
        {
            cout << "zifan:" << endl;
            cout << "{}" << endl;
            return;
        }
        set<pair<string, string>> not_in_base(all_relations);

        for (auto &i : reflexive_base)
        {
            if (not_in_base.find(i) != not_in_base.end())
            {
                not_in_base.erase(i);
            }
        }

        int insert_count = 1 << not_in_base.size();

        cout << "zifan:" << endl;
        for (size_t i = 0; i < insert_count; ++i)
        {
            set<pair<string, string>> temp(reflexive_base);
            vector<pair<string, string>> nib_v(not_in_base.begin(), not_in_base.end());
            for (size_t j = 0; j < not_in_base.size(); ++j)
            {
                if ((i >> j) & 1)
                {
                    temp.insert(nib_v[j]);
                }
            }
            cout << "{";
            for (auto &i : temp)
            {
                cout << "<" << i.first << "," << i.second << ">";

                auto it = prev(temp.end());
                if (i != *it)
                {
                    cout << ",";
                }
            }
            cout << "}" << endl;
        }
    }

    void print_symmetric()
    {
        if (count == 0)
        {
            cout << "duichen:" << endl;
            cout << "{}" << endl;
            return;
        }
        int insert_count = 1 << all_relations.size();
        set<string> output;

        cout << "duichen:" << endl;
        for (size_t i = 0; i < insert_count; ++i)
        {
            set<pair<string, string>> temp;
            vector<pair<string, string>> v(all_relations.begin(), all_relations.end());
            for (size_t j = 0; j < all_relations.size(); ++j)
            {
                if ((i >> j) & 1)
                {
                    temp.insert(v[j]);
                }
            }

            if (isSymmetric(temp))
            {
                stringstream ss;
                ss << "{";
                for (auto &i : temp)
                {
                    ss << "<" << i.first << "," << i.second << ">";

                    auto it = prev(temp.end());
                    if (i != *it)
                    {
                        ss << ",";
                    }
                }
                ss << "}" << endl;
                output.insert(ss.str());
            }
        }

        vector<string> output_v(output.begin(), output.end());
        sort(output_v.begin(), output_v.end(), [](string &a, string &b)
             { return a.length() < b.length(); });

        for (auto &i : output_v)
        {
            cout << i;
        }
    }

private:
    string raw_input;
    size_t count;
    set<string> s;
    set<pair<string, string>> all_relations;
    set<pair<string, string>> reflexive_base;

    void init_relations()
    {
        for (auto &i : s)
        {
            for (auto &j : s)
            {
                all_relations.insert({i, j});
            }
            reflexive_base.insert({i, i});
        }
    }

    bool isSymmetric(set<pair<string, string>> input)
    {
        bool isSymmetric_r = true;
        for (auto &i : input)
        {
            if (input.find({i.second, i.first}) == input.end())
            {
                isSymmetric_r = false;
            }
        }
        return isSymmetric_r;
    }
};

int main()
{
    size_t count;
    string input;
    cin >> count >> input;

    relations re(input, count);
    // re.traverse_s();
    // re.traverse_all_relations();
    re.print_reflexive();
    re.print_symmetric();
    return 0;
}