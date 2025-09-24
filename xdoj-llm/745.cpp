#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iomanip>

typedef struct Node_Data {
    int Address;
    int Key;
    int Next;
} Node_Data;

int main()
{
    // 输入获取
    int iHead, iCount;
    if (!(std::cin >> iHead >> iCount)) return 0;

    // 使用哈希表存储所有节点，便于按地址查找
    std::unordered_map<int, Node_Data> nodes;
    nodes.reserve(iCount);
    for (int i = 0; i < iCount; ++i) {
        Node_Data n;
        std::cin >> n.Address >> n.Key >> n.Next;
        nodes[n.Address] = n;
    }

    // 从头指针按 Next 真实遍历（visited 防止成环）
    std::unordered_set<int> visited;
    visited.reserve(iCount);
    std::vector<int> order;
    order.reserve(iCount);
    for (int p = iHead; p != -1 && nodes.count(p) && !visited.count(p); p = nodes[p].Next) {
        order.push_back(p);
        visited.insert(p);
    }

    // 绝对值去重：保留首次出现
    std::unordered_set<int> seenAbs;
    seenAbs.reserve(order.size());
    std::vector<int> kept;
    kept.reserve(order.size());
    for (int addr : order) {
        int ak = nodes[addr].Key;
        ak = ak >= 0 ? ak : -ak;
        if (seenAbs.insert(ak).second) {
            kept.push_back(addr);
        }
    }

    // 输出：根据 kept 顺序重建 Next（最后一个为 -1）
    std::cout << kept.size() << std::endl;
    for (size_t i = 0; i < kept.size(); ++i) {
        int addr = kept[i];
        int nextAddr = (i + 1 < kept.size()) ? kept[i + 1] : -1;
        std::cout << std::setw(5) << std::setfill('0') << addr
                  << " " << nodes[addr].Key << " ";
        if (nextAddr == -1) {
            std::cout << -1 << "\n";
        } else {
            std::cout << std::setw(5) << std::setfill('0') << nextAddr << "\n";
        }
        std::cout << std::setfill(' ');
    }

    return 0;
}