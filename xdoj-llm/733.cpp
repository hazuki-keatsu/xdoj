#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    int sum = 0;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    while (arr.size() > 1) {
        std::sort(arr.begin(), arr.end());
        int temp = arr[0] + arr[1];
        sum += temp;
        arr.erase(arr.begin(), arr.begin() + 2);
        arr.push_back(temp);
    }

    std::cout << sum << std::endl;

    return 0;
}
