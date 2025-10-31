#include <iostream>
#include <vector>

int main() {
    int m, p;
    std::cin >> m >> p;

    std::vector<int> hash_table(m, -2);
    int count = 0;

    int key;
    while(std::cin >> key) {
        if (key == -1) {
            break;
        }

        bool exists = false;
        int pos = -1;
        for (int i = 0; i < m; ++i) {
            if (hash_table[i] == key) {
                exists = true;
                pos = i;
                break;
            }
        }
        if (exists) {
            std::cout << pos << std::endl;
            continue;
        }

        if (count == m - 1) {
            std::cout << "Table full" << std::endl;
            break;
        }

        int initial = key % p;
        for (int i = 0; i < m; ++i) {
            int curr_pos = (initial + i) % m;
            if (hash_table[curr_pos] == -2) {
                hash_table[curr_pos] = key;
                count++;
                std::cout << curr_pos << std::endl;
                break;
            }
        }
    }

    return 0;
}