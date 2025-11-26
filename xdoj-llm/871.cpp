#include <iostream>
#include <vector>
#include <set>

void insertSort(std::vector<int> &toSort)
{
    std::set<int> toReturn;

    for (int i = 0; i < toSort.size(); i++)
    {
        toReturn.insert(toSort[i]);
        if (toReturn.size() > 1)
        {
            for (auto i : toReturn)
            {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main()
{
    std::vector<int> arr;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; i++) {
        int temp;
        std::cin >> temp;
        arr.push_back(temp);
    }

    insertSort(arr);

    return 0;
}