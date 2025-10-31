#include <iostream>
#include <sstream>

int main() {
    int x, y;
    std::stringstream result;
    while (std::cin >> x >> y) {
        if (x == 0 && y == 0) break;
        while (x != y) {
            if (x > y) x /= 2;
            else y /= 2;
        }
        result << x << std::endl;
    }
    std::cout << result.str() << std::endl;
    return 0;
}