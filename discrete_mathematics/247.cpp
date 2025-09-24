#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>> transitive_closure_once(vector<vector<bool>> input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t j = 0; j < input.size(); j++)
        {
            for (size_t k = 0; k < input.size(); k++)
            {
                if (input[i][j] == true && input[j][k] == true)
                {
                    input[i][k] = true;
                }
            }
        }
    }
    return input;
}

vector<vector<bool>> transitive_closure(vector<vector<bool>> input)
{
    while (true)
    {
        bool isTransitive = true;

        for (size_t i = 0; i < input.size(); i++)
        {
            for (size_t j = 0; j < input.size(); j++)
            {
                for (size_t k = 0; k < input.size(); k++)
                {
                    if (input[i][j] == true && input[j][k] == true && input[i][k] != true)
                    {
                        isTransitive = false;
                    }
                }
            }
        }

        if (isTransitive == false)
        {
            input = transitive_closure_once(input);
        }
        else
        {
            break;
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

    auto trans = transitive_closure(matrix);

    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            cout << (trans[i][j] == true ? "1" : "0") << " ";
        }
        cout << endl;
    }

    return 0;
}