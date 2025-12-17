#include <iostream>
#include <vector>
#include <algorithm>

struct Edge
{
    int start;
    int end;
    int value;

    Edge(int start, int end, int value) : start(start), end(end), value(value) {}
};

class UnionFind
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
            return false;

        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

int main()
{
    std::vector<Edge> map;

    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    map.reserve(edge_count);

    for (int i = 0; i < edge_count; i++)
    {
        int start, end, value;
        std::cin >> start >> end >> value;
        if (start > end)
            std::swap(start, end);
        map.push_back(Edge(start, end, value));
    }

    std::sort(map.begin(), map.end(), [](Edge one, Edge two)
              { return one.value < two.value; });

    UnionFind uf(vertex_count);
    std::vector<Edge> toOutput;

    for (auto& edge : map)
    {
        if (uf.unite(edge.start - 1, edge.end - 1))
        {
            toOutput.push_back(edge);
        }
    }

    for (auto& i : toOutput)
    {
        std::cout << i.start << " " << i.end << " " << i.value << std::endl;
    }

    return 0;
}