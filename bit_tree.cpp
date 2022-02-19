//
// Created by jyh on 2月20日.
//

#include <vector>
#include <iostream>
using namespace std;

// 树状数组
// BitTree bt(100); // n = 100
// bt.add(0, 11);   // position 0, add 11
// bt.add(99, 22);  // position 99, add 22
// bt.sum(99); // 33, from position 0 and position 99
// bt.add(100, 1); // ERROR! 100 >= n
class BitTree {
    int n;
    vector<int> sums; // 树从[0]开始
public:
    // n 要比最大的可能add的数大1
    explicit BitTree(int n): n(n), sums(n) {}
    // add 位置 x 的数值增加 y
    // 0 <= x < n
    void add(int x, int y) {
        for (++x; x <= n; x += x & -x) {
            sums[x - 1] += y;
        }
    }
    // sum 统计位置 0 到 位置 x 的总和
    // 0 <= x < n
    int sum(int x) {
        int ans = 0;
        for (++x; x; x -= x & -x) {
            ans += sums[x - 1];
        }
        return ans;
    }
};

int main() {
    BitTree bt(100);
    bt.add(3, 10);
    bt.add(5, 10);
    cout << bt.sum(2) << endl; // 0
    cout << bt.sum(3) << endl; // 10
    cout << bt.sum(4) << endl; // 10
    cout << bt.sum(5) << endl; // 20
    return 0;
}
