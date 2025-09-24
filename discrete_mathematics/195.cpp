#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int count;
    cin >> count;
    vector<vector<bool>> map(count, vector<bool>(count));
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            int buffer;
            cin >> buffer;
            if (buffer == 1)
            {
                map[i][j] = true;
            }
            else
            {
                map[i][j] = false;
            }
        }
    }

    bool isEquality = true;

    // 自反性
    for (int i = 0; i < count; i++)
    {
        if (map[i][i] != 1)
        {
            isEquality = false;
        }
    }

    // 对称性
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (map[i][j] != map[j][i])
            {
                isEquality = false;
            }
        }
    }

    // 传递性
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            for (int k = 0; k < count; k++)
            {
                if (map[i][j] == 1 && map[j][k] == 1)
                {
                    if (map[i][k] != 1)
                    {
                        isEquality = false;
                    }
                }
            }
        }
    }

    cout << (isEquality == true ? "yes" : "no") << endl;

    return 0;
}