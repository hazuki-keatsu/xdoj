#include <iostream>
#include <vector>
using namespace std;

int main() {  
    int N;
    if (!(cin >> N)) return 0;
    vector<int> q;
    q.reserve(N);
    for (int i = 1; i <= N; ++i) q.push_back(i);

    int round = 0;
    while ((int)q.size() > 3) {
        ++round;
        int d = (round % 2 == 1) ? 2 : 3;
        vector<int> next;
        next.reserve(q.size());
        // 按当前位置计数，去除计数为 d 的倍数的元素
        for (int i = 0; i < (int)q.size(); ++i) {
            // 当前轮的计数位置（从1开始）
            int pos = i + 1;               
            if (pos % d != 0) next.push_back(q[i]);
        }
        q.swap(next);
    }

    for (size_t i = 0; i < q.size(); ++i) {
        if (i) cout << ' ';
        cout << q[i];
    }
    return 0;
}
