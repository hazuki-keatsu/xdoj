#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <string>

int main() {
    while(true) {
        int n;
        std::cin >> n;
        if (n == 0) {
            break;
        }
        
        // 读取 count 个元素
        std::queue<int> elements;
        for (int i = 0; i < n; i++) {
            int temp;
            std::cin >> temp;
            elements.push(temp);
        }

        // 按层次分组
        size_t layer = 0;
        std::vector<std::string> results;
        while(!elements.empty()) {
            std::string result = "";
            size_t layerSize = (1 << layer);
            size_t actualSize = std::min(layerSize, elements.size());
            for (size_t i = 0; i < actualSize; i++) {
                int top = elements.front();
                elements.pop();
                result += std::to_string(top);
                result += " ";
            }
            results.push_back(result);
            layer++;
        }

        // 读取目标层次
        int target;
        std::cin >> target;
        if (target > (int)results.size() || target < 1) {
            std::cout << "EMPTY" << std::endl;
        } else {
            std::cout << results[target - 1] << std::endl;
        }
    }
    
    return 0;
}