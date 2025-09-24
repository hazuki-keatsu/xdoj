#include <iostream>
#include <map>

// 测试案例给那么少，负数输不输出括号也不说清楚，什么B玩意题目，话都不会讲了吗

int main()
{
    int n, m, t;
    std::cin >> n >> m >> t;
    // n表示第一个多项式的项数
    // m表示第二个多项式的项数
    // t表示运算法则，0为加法，1为减法

    std::map<int, int> map = std::map<int, int>();

    int max_in, min_in;
    max_in = -1000000;  // 初始化为极小值
    min_in = 1000000;   // 初始化为极大值

    for (int i = 0; i < n; i++)
    {
        int para, in;
        std::cin >> para >> in;
        if (in > max_in) max_in = in;
        if (in < min_in) min_in = in;
        map[in] += para;
    }
    for (int i = 0; i < m; i++)
    {
        int para, in;
        std::cin >> para >> in;
        if (in > max_in) max_in = in;
        if (in < min_in) min_in = in;
        if (t == 0)
        {
            map[in] += para;
        } else if (t == 1) {
            map[in] -= para;
        } else {
            return -1;
        }
    }

    bool isFirst = true;
    bool hasOutput = false;
    for(int i = min_in; i <= max_in; i++) {
        if (map[i] == 0) continue;
        hasOutput = true;
        if (isFirst) {
            if (i == 0) {
                std::cout << map[i];
            } else if (i == 1) {
                if (map[i] == 1) {
                    std::cout << "x";
                } else if (map[i] == -1) {
                    std::cout << "-x";
                } else {
                    std::cout << map[i] << "x";
                }
            } else if (i > 0) {
                if (map[i] == 1) {
                    std::cout << "x^" << i;
                } else if (map[i] == -1) {
                    std::cout << "-x^" << i;
                } else {
                    std::cout << map[i] << "x^" << i;
                }
            } else {
                if (map[i] == 1) {
                    // std::cout << "x^(" << i << ")";
                    std::cout << "x^" << i;
                } else if (map[i] == -1) {
                    // std::cout << "-x^(" << i << ")";
                    std::cout << "-x^" << i;
                } else {
                    // std::cout << map[i] << "x^(" << i << ")";
                    std::cout << map[i] << "x^" << i;
                }
            }
            isFirst = false;
        } else {
            if (map[i] > 0) {
                if (i == 0) {
                    std::cout << "+" << map[i];
                } else if (i == 1) {
                    if (map[i] == 1) {
                        std::cout << "+" << "x";
                    } else {
                        std::cout << "+" << map[i] << "x";
                    }
                } else if (i > 0) {
                    if (map[i] == 1) {
                        std::cout << "+" << "x^" << i;
                    } else {
                        std::cout << "+" << map[i] << "x^" << i;
                    }
                } else {
                    if (map[i] == 1) {
                        // std::cout << "+" << "x^(" << i << ")";
                        std::cout << "+" << "x^" << i;
                    } else {
                        // std::cout << "+" << map[i] << "x^(" << i << ")";
                        std::cout << "+" << map[i] << "x^" << i;
                    }
                }
            } else {
                if (i == 0) {
                    std::cout << map[i];
                } else if (i == 1) {
                    if (map[i] == -1) {
                        std::cout << "-" << "x";
                    } else {
                        std::cout << map[i] << "x";
                    }
                } else if (i > 0) {
                    if (map[i] == -1) {
                        std::cout << "-" << "x^" << i;
                    } else {
                        std::cout << map[i] << "x^" << i;
                    }
                } else {
                    if (map[i] == -1) {
                        // std::cout << "-" << "x^(" << i << ")";
                        std::cout << "-" << "x^" << i;
                    } else {
                        // std::cout << map[i] << "x^(" << i << ")";
                        std::cout << map[i] << "x^" << i;
                    }
                }
            }
        }
    }
    
    if (!hasOutput) {
        std::cout << "0";
    }
    std::cout << std::endl;
    return 0;
}