#include <iostream>
#include <vector>
#include <utility>

void findTheShortestRoad(std::vector<std::vector<int>> adj, int start, int end) {
    int n = adj.size();
    std::vector<int> dist(n, 10000);
    std::vector<int> parent(n, -1);
    std::vector<bool> visit(n, false);
    
    dist[start] = 0;
    
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visit[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        
        if (u == -1 || dist[u] == 10000) break;
        
        visit[u] = true;
        
        for (int v = 0; v < n; v++) {
            if (adj[u][v] > 0 && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
            }
        }
    }
    
    if (dist[end] == 10000) {
        std::cout << "NO" << std::endl;
    } else {
        std::cout << dist[end] << std::endl;
        
        std::vector<int> path;
        int current = end;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        
        for (int i = path.size() - 1; i >= 0; i--) {
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int vertex_count;
    std::cin >> vertex_count;

    std::vector<std::vector<int>> adj(vertex_count, std::vector<int>(vertex_count, 0));

    for (int i = 0; i < vertex_count; i ++) {
        for (int j = 0; j < vertex_count; j ++) {
            int temp;
            std::cin >> temp;
            adj[i][j] = temp;
        }
    }

    std::vector<std::pair<int, int>> to_search;
    while(true) {
        int start, end;
        std::cin >> start >> end;
        if (start == -1 || end == -1) {
            break;
        }
        to_search.push_back(std::pair<int, int>(start, end));
    }

    for (auto& query : to_search) {
        findTheShortestRoad(adj, query.first, query.second);
    }

    return 0;
}