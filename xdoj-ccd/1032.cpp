#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

class maze_finder
{
private:
    vector<vector<bool>> map;
    pair<int, int> start;
    pair<int, int> end;
    int s_length;
    vector<pair<int, int>> path;

    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};

    void findToOut() {
        int n = map.size();
        // 记录访问状态和距离
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        vector<vector<int>> distance(n, vector<int>(n, -1));
        // 记录路径
        vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(n));
        
        queue<pair<int,int>> q;
        q.push(start);
        visited[start.first][start.second] = true;
        distance[start.first][start.second] = 0;

        bool found = false;
        while (!q.empty() && !found) {
            pair<int,int> current = q.front();
            q.pop();

            // 检查四个方向
            for (int i = 0; i < 4; i++) {
                int new_x = current.first + dx[i];
                int new_y = current.second + dy[i];

                // 检查是否在边界内且可以访问
                if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n 
                    && !map[new_x][new_y] && !visited[new_x][new_y]) {
                    
                    visited[new_x][new_y] = true;
                    distance[new_x][new_y] = distance[current.first][current.second] + 1;
                    parent[new_x][new_y] = current;
                    
                    pair<int,int> next(new_x, new_y);
                    q.push(next);

                    if (next == end) {
                        found = true;
                        break;
                    }
                }
            }
        }

        // 如果找到路径，记录路径
        if (visited[end.first][end.second]) {
            s_length = distance[end.first][end.second];
            // 重建路径
            pair<int,int> current = end;
            while (current != start) {
                path.push_back(current);
                current = parent[current.first][current.second];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
        }
    }

public:
    maze_finder(vector<vector<bool>> &maze, pair<int, int> &start, pair<int, int> &end)
        : map(maze), start(start), end(end)
    {
        findToOut();
    }

    // 遍历
    void traverse()
    {
        cout << start.first << " " << start.second << " " << end.first << " " << end.second << endl;

        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[i].size(); j++)
            {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }

    int getLength() const {
        return s_length;
    }

    const vector<pair<int,int>>& getPath() const {
        return path;
    }
};

int main()
{
    int n;
    pair<int, int> start, end;
    cin >> n >> start.first >> start.second >> end.first >> end.second;

    start.first -= 1;
    start.second -= 1;
    end.first -= 1;
    end.second -= 1;

    vector<vector<bool>> maze(n, vector<bool>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int buffer;
            cin >> buffer;
            if (buffer == 1)
            {
                maze[i][j] = true;
            }
            else
            {
                maze[i][j] = false;
            }
        }
    }

    maze_finder mf(maze, start, end);

    cout << mf.getLength() << endl;
    for (auto &i : mf.getPath())
    {
        cout << "(" << i.first + 1 << "," << i.second + 1 << ")";
    }
    cout << endl;

    return 0;
}