#include <iostream>
#include <vector>

int partitionOfQuickSort(std::vector<int> &nums, int low, int high) {
    int pivotKey = nums[low];
    while (low < high) {
        while (low < high && nums[high] >= pivotKey) --high;
        nums[low] = nums[high];
        while (low < high && nums[low] <= pivotKey) ++low;
        nums[high] = nums[low];
    }
    nums[low] = pivotKey;
    return low;
}

void quickSort(std::vector<int> &nums, int low, int high) {
    if (low < high) {
        int pivotLoc = partitionOfQuickSort(nums, low, high);
        quickSort(nums, low, pivotLoc - 1);
        quickSort(nums, pivotLoc + 1, high);
        std::cout << nums[pivotLoc] << " ";
    } else if (low == high) {
        std::cout << nums[low] << " ";
    }
}

void qSort(std::vector<int> &nums) {
    if (nums.empty()) return;
    int low = 0;
    int high = static_cast<int>(nums.size()) - 1;
    quickSort(nums, low, high);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    
    qSort(v);
    std::cout << std::endl;
    
    return 0;
}