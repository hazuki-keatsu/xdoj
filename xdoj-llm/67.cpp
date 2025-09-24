#include <iostream>

class vector_int {
private:
    int* data;
    size_t size_;
    size_t capacity_;

public:
    vector_int() : data(nullptr), size_(0), capacity_(0) {};
    vector_int(int size) : data(nullptr), size_(0), capacity_(size) {
        data = new int[capacity_];
    };

    void push_back(const int& value) {
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            int* new_data = new int[new_capacity];

            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;

            data = new_data;
            capacity_ = new_capacity;
        }
        data[size_++] = value;
    }

    int* begin() {
        return &(data[0]);
    }

    int* end() {
        return &(data[size_-1])+1;
    }
};

int main() {
    int n, k;

    std::cin >> n >> k;

    vector_int vec = vector_int();

    for (int i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        vec.push_back(temp);
    }

    bool flag = false;

    for (auto i = vec.begin(); i < vec.end(); i++) {
        if (*i == k) {
            std::cout << i - vec.begin() << " ";
            flag = true;
        }
    }
    if (flag != true) {
        std::cout << "-1";
    }
}