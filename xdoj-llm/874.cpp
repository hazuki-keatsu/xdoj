#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n, std::vector<int>(n));
    std::vector<int> inDegree(n, 0);
    
    // 读取邻接矩阵并计算入度
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> adj[i][j];
            if (adj[i][j] > 0) {
                inDegree[j]++;
            }
        }
    }
    
    // 拓扑排序 + 计算最早发生时间（最长路径）
    std::vector<int> ve(n, 0);  // ve[i] 表示事件i的最早发生时间
    std::queue<int> q;
    std::vector<int> tempInDegree = inDegree;
    
    // 将入度为0的顶点入队
    for (int i = 0; i < n; i++) {
        if (tempInDegree[i] == 0) {
            q.push(i);
        }
    }
    
    int count = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        count++;
        
        // 处理u的所有后继
        for (int v = 0; v < n; v++) {
            if (adj[u][v] > 0) {
                // 更新最早发生时间（取最长路径）
                ve[v] = std::max(ve[v], ve[u] + adj[u][v]);
                tempInDegree[v]--;
                if (tempInDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
    
    // 如果拓扑排序没有遍历所有顶点，则有环
    if (count != n) {
        std::cout << "NO" << std::endl;
    } else {
        std::cout << ve[n - 1] << std::endl;
    }
    
    return 0;
}