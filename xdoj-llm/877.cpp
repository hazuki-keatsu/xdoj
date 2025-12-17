#include <iostream>
#include <vector>

std::vector<bool> visit;
std::vector<int> dfs_result;
std::vector<std::vector<bool>> adj;
int vertex_count;

void dfs(int u) {
    visit[u] = true;
    dfs_result.push_back(u + 1);
    
    for (int v = 0; v < vertex_count; v++) {
        if (adj[u][v] && !visit[v]) {
            dfs(v);
        }
    }
}

int main() {
    std::cin >> vertex_count;

    adj.resize(vertex_count, std::vector<bool>(vertex_count, false));

    for(int i = 0; i < vertex_count; i++) {
        for(int j = 0; j < vertex_count; j++) {
            int temp;
            std::cin >> temp;
            if (temp == 1) {
                adj[i][j] = true;
            }
        }
    }

    visit.resize(vertex_count, false);
    int connected_components = 0;

    for(int start = 0; start < vertex_count; start ++) {
        if (!visit[start]) {
            connected_components++;
            dfs(start);
        }
    }

    for (int i = 0; i < dfs_result.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << dfs_result[i];
    }
    std::cout << std::endl;

    std::cout << connected_components << std::endl;

    return 0;
}