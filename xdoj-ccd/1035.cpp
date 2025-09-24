#include <iostream>
#include <vector>

using namespace std;

int count = 0;
int n, c;

// 检查当前位置是否可以放置皇后
bool isSafe(const vector<int> &cols, int row, int col)
{
    for (int i = 0; i < row; ++i)
    {
        if (cols[i] == col || abs(cols[i] - col) == abs(i - row))
        {
            return false;
        }
    }
    return true;
}

// 回溯函数
void solveNQueens(int row, vector<int> &cols)
{
    if (row == n)
    {
        count++;
        return;
    }

    for (int col = 0; col < n; ++col)
    {
        if (isSafe(cols, row, col))
        {
            cols[row] = col;
            solveNQueens(row + 1, cols);
        }
    }
}

int main()
{
    cin >> n >> c;
    c--;

    vector<int> cols(n, -1);
    cols[0] = c;

    solveNQueens(1, cols);

    cout << count << endl;

    return 0;
}