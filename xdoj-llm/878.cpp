#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

int main() {
    int edge_count, vertex_count, start;
    std::cin >> edge_count >> vertex_count >> start;
    start--;

    std::vector<std::vector<std::pair<int, int>>> adj(vertex_count);

    for (int i = 0; i < edge_count; i++) {
        int source, target, time;
        std::cin >> source >> target >> time;
        source--;
        target--;
        adj[source].push_back({target, time});
    }

    std::vector<int> dist(vertex_count, INT_MAX);
    std::vector<bool> visit(vertex_count, false);
    
    dist[start] = 0;

    for (int i = 0; i < vertex_count; i++) {
        int u = -1;
        for (int j = 0; j < vertex_count; j++) {
            if (!visit[j] && dist[j] != INT_MAX) {
                if (u == -1 || dist[j] < dist[u]) {
                    u = j;
                }
            }
        }
        
        if (u == -1) break;
        
        visit[u] = true;
        
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    int max_time = 0;
    for (int i = 0; i < vertex_count; i++) {
        if (dist[i] == INT_MAX) {
            std::cout << -1 << std::endl;
            return 0;
        }
        max_time = std::max(max_time, dist[i]);
    }

    std::cout << max_time << std::endl;

    return 0;
}