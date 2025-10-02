#include <iostream>
#include <vector>
#include <functional>
using namespace std;

struct Node
{
    int i, j, d;
}; // d 为走向下一格的方向

int main()
{
    int m, n; // m: 行(高度)  n: 列(宽度)
    if (!(cin >> m >> n))
        return 0;
    int si, sj, ti, tj; // 起点 终点 (1-based)
    cin >> si >> sj;
    cin >> ti >> tj;
    if (m <= 0 || n <= 0 || m >= 105 || n >= 105)
    {
        cout << "no";
        return 0; // 简单防御
    }
    vector<vector<int>> a(m + 1, vector<int>(n + 1, 1));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    }

    // 如果起点或终点是障碍
    if (a[si][sj] == 1 || a[ti][tj] == 1)
    {
        cout << "no";
        return 0;
    }

    // 特殊: 起点即终点
    if (si == ti && sj == tj)
    {
        cout << '(' << si << ',' << sj << ',' << 1 << ')';
        return 0;
    }

    vector<vector<int>> vis(m + 1, vector<int>(n + 1, 0));
    vector<Node> path; // 结果路径

    // 方向: 右 下 左 上
    const int di[5] = {0, 0, 1, 0, -1};
    const int dj[5] = {0, 1, 0, -1, 0};

    bool found = false;
    function<bool(int, int)> dfs = [&](int r, int c) -> bool
    {
        if (r == ti && c == tj)
            return true; // 到达终点
        for (int d = 1; d <= 4; ++d)
        {
            int nr = r + di[d];
            int nc = c + dj[d];
            if (nr < 1 || nr > m || nc < 1 || nc > n)
                continue;
            if (a[nr][nc] == 1 || vis[nr][nc])
                continue;
            vis[nr][nc] = 1;
            path.push_back({r, c, d}); // 当前格走向 d
            if (dfs(nr, nc))
                return true; // 若成功, 直接返回
            path.pop_back(); // 回溯
        }
        return false;
    };

    vis[si][sj] = 1;
    found = dfs(si, sj);
    if (!found)
    {
        cout << "no";
        return 0;
    }
    // 添加终点三元组, 按样例对终点设置 d=1
    path.push_back({ti, tj, 1});

    // 输出
    for (size_t k = 0; k < path.size(); ++k)
    {
        cout << '(' << path[k].i << ',' << path[k].j << ',' << path[k].d << ')';
        if (k + 1 < path.size())
            cout << ',';
    }
    return 0;
}
