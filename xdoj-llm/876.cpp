#include <iostream>
#include <vector>
#include <queue>

int main() {
    int vertex_count;
    std::cin >> vertex_count;

    std::vector<std::vector<bool>> adj(vertex_count, std::vector<bool>(vertex_count, false));

    for(int i = 0; i < vertex_count; i++) {
        for(int j = 0; j < vertex_count; j++) {
            int temp;
            std::cin >> temp;
            if (temp == 1) {
                adj[i][j] = true;
            }
        }
    }

    std::vector<bool> visit(vertex_count, false);
    std::vector<int> bfs_result;
    int connected_components = 0;

    for (int start = 0; start < vertex_count; start++) {
        if (!visit[start]) {
            connected_components++;
            std::queue<int> q;
            q.push(start);
            visit[start] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                bfs_result.push_back(u + 1);

                for (int v = 0; v < vertex_count; v++) {
                    if (adj[u][v] && !visit[v]) {
                        visit[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    for (int i = 0; i < bfs_result.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << bfs_result[i];
    }
    std::cout << std::endl;

    std::cout << connected_components << std::endl;

    return 0;
}