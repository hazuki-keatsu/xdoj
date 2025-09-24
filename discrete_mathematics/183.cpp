#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>> reflexive_closure(vector<vector<bool>> input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        input[i][i] = true;
    }
    return input;
}

vector<vector<bool>> symmetric_closure(vector<vector<bool>> input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t j = 0; j < input.size(); j++)
        {
            if (input[i][j] == true)
            {
                input[j][i] = true;
            }
        }
    }
    return input;
}

int main()
{
    int count;
    cin >> count;
    vector<vector<bool>> matrix(count, vector<bool>(count));
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            int buffer;
            cin >> buffer;
            if (buffer == 1)
            {
                matrix[i][j] = true;
            }
            else
            {
                matrix[i][j] = false;
            }
        }
    }

    auto re = reflexive_closure(matrix);

    auto sym = symmetric_closure(matrix);

    cout << "r(R):" << endl;
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            cout << (re[i][j] == true ? "1" : "0") << " ";
        }
        cout << endl;
    }

    cout << "s(R):" << endl;
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            cout << (sym[i][j] == true ? "1" : "0") << " ";
        }
        cout << endl;
    }

    return 0;
}