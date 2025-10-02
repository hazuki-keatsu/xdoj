#include <iostream>
#include <stack>

int main (){
    // input
    size_t n;
    std::cin >> n;
    int *elems = new int[n];
    for(size_t i = 0; i < n; i++) {
        std::cin >> elems[i];
    }

    int step = 1;
    int idx = 0;
    std::stack<int> s;

    for(size_t i = 1; i <= 2 * n; i++) {
        if (!s.empty() && s.top() == elems[idx]) {
            s.pop();
            idx++;
        } else {
            s.push(step);
            step++;
        }
    }

    if(s.empty()) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }

    // release
    delete elems;
    return 0;
}