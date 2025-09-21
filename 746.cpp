#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::vector<int> l;
    l.reserve(a + b);
    for(size_t i = 0; i < a + b; i++) {
        int temp;
        std::cin >> temp;
        l.push_back(temp);
    }
    
    std::sort(l.begin(),l.end());

    // 去重：相邻去重 + 擦除（线性复杂度）
    l.erase(std::unique(l.begin(), l.end()), l.end());

    // 输出去重后的序列
    for (size_t i = 0; i < l.size(); ++i) {
        std::cout << l[i] << " ";
    }

    return 0;
}