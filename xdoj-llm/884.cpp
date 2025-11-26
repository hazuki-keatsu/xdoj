#include <iostream>
#include <vector>
#include <map>
#include <set>

void statisticByGroup() {
    int count;
    std::cin >> count;
    std::map<int, std::map<int, int>> map;
    std::vector<int> element, group;
    std::set<int> s;

    for (int i = 0; i < count; i++) {
        int temp;
        std::cin >> temp;
        element.push_back(temp);
        s.insert(temp);
    }
    for (int i = 0; i < count; i++) {
        int temp;
        std::cin >> temp;
        group.push_back(temp);
    }

    for (int i = 0; i < count; i++) {
        if (map.count(group[i])) {
            if (map[group[i]].count(element[i])) {
                map[group[i]][element[i]] += 1;
            } else {
                map[group[i]].insert({element[i], 1});
            }
        } else {
            map.insert(std::make_pair(group[i], std::map<int, int>{{element[i], 1}}));
        }
    }

    for (auto i : map) {
        std::cout << i.first << "={";
        int iCount = s.size();
        int k = 0;
        for (auto j : s) {
            k++;
            std::cout << j << "=" << i.second[j];
            if (k != iCount) std::cout << ",";
        }
        std::cout << "}" << std::endl;
    }
}

int main() {
    int testCount;
    std::cin >> testCount;
    for(int i = 0; i < testCount; i++) {
        statisticByGroup();
    }

    return 0;
}