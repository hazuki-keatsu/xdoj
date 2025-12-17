#include <iostream>
#include <vector>

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

    int countSets() {
        int count = 0;
        int size = parent.size();
        for (int i = 0; i < size; i++) {
            if (find(i) == i) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    int city, rail;
    std::cin >> city >> rail;

    UnionFind unionFind(city);
    for(int i = 0; i < rail; i++) {
        int a, b;
        std::cin >> a >> b;
        unionFind.unite(a - 1, b - 1);
    }

    std::cout << unionFind.countSets() - 1 << std::endl;

    return 0;
}