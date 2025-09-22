#include <iostream>
#include <queue>

int main () {
    int n;
    std::cin >> n;
    std::queue<int> q;
    for(size_t i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        q.push(temp);
    }

    std::queue<int> even;
    std::queue<int> odd;
    int marker = 1;
    while(!q.empty()) {
        if (marker % 2 == 0) { // 偶数
            even.push(q.front());
        } else {
            odd.push(q.front());
        }
        q.pop();
        marker++;
    }

    while(!odd.empty()) {
        std::cout << odd.front() << " ";
        odd.pop();
    }

    while(!even.empty()) {
        std::cout << even.front() << " ";
        even.pop();
    }

    return 0;
}