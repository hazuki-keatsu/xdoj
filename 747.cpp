#include <iostream>
#include <vector>
#include <stack>

int main()
{
    int lineCount;
    std::cin >> lineCount;
    std::vector<std::stack<int>> matrix(lineCount);

    for(size_t i = 0; i < lineCount; i++) {
        int count;
        std::cin >> count;
        for(size_t j = 0; j < count; j++) {
            int temp;
            std::cin >> temp;
            matrix[i].push(temp);
        }
    }

    for(size_t i = 0; i < lineCount; i++) {
        while(!matrix[i].empty()) {
            std::cout << matrix[i].top() << " ";
            matrix[i].pop();
        }
        std::cout << std::endl;
    }
}