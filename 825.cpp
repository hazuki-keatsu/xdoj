#include <iostream>
#include <vector>

int main()
{
    size_t count;
    std::vector<char> v;
    std::cin >> count;
    if (count == 0)
    {
        std::cout << "YES" << std::endl;
        return 0;
    }
    for (size_t i = 0; i < count; i++)
    {
        char temp;
        std::cin >> temp;
        v.push_back(temp);
    }

    // for(auto it : v) {
    //     std::cout << it;
    // }

    auto begin = v.begin();
    auto end = v.end() - 1;

    bool flag = true;
    while (begin < end)
    {
        if (*begin != *end)
        {
            flag = false;
        }
        begin++;
        end--;
    }
    if (flag)
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }

    return 0;
}