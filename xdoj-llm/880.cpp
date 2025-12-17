#include <iostream>
#include <vector>
#include <queue>

bool kahnSession()
{
    int count;
    std::cin >> count;

    std::vector<std::vector<bool>> adj(count, std::vector<bool>(count, false));

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            int temp;
            std::cin >> temp;
            adj[i][j] = temp == 1 ? true : false;
        }
    }

    std::vector<int> inDegree(count, 0);
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (adj[i][j])
            {
                inDegree[j]++;
            }
        }
    }

    std::queue<int> q;
    std::vector<int> topo;
    
    for (int i = 0; i < count; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (int v = 0; v < count; v++)
        {
            if (adj[u][v])
            {
                inDegree[v]--;
                if (inDegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }
    }

    return topo.size() == count;
}

int main()
{
    int count;
    std::cin >> count;

    std::vector<bool> results;
    for (int i = 0; i < count; i++)
    {
        results.push_back(kahnSession());
    }

    for (int i = 0; i < results.size(); i++)
    {
        std::cout << (results[i] ? 0 : 1);
    }
    std::cout << std::endl;

    return 0;
}