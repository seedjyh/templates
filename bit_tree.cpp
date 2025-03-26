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
    vector<LL> sums; // 树从[0]开始
public:
    // n 要比最大的可能add的数大1
    explicit BitTree(int n): n(n), sums(n) {}
    // add 位置 pos 的数值增加 diff
    // 0 <= pos < n
    void add(int pos, LL diff) {
        for (++pos; pos <= n; pos += pos & -pos) {
            sums[pos - 1] += diff;
        }
    }
    // sum 统计位置 0 到 位置 pos 的总和
    // 0 <= pos < n
    LL sum(int pos) {
        int ans = 0;
        for (++pos; pos; pos -= pos & -pos) {
            ans += sums[pos - 1];
        }
        return ans;
    }
};

// 带模的树状数组
// BitTreeMod bt(100, 1e9 + 7); // n = 100
// bt.add(0, 11);   // position 0, add 11
// bt.add(99, 22);  // position 99, add 22
// bt.sum(99); // 33, from position 0 and position 99
// bt.add(100, 1); // ERROR! 100 >= n
class BitTreeMod {
    int n;
    int mod_;
    vector<LL> sums; // 树从[0]开始
public:
    // n 要比最大的可能add的数大1
    explicit BitTreeMod(int n, int mod): n(n), mod_(mod), sums(n) {}
    // add 位置 x 的数值增加 y
    // 0 <= x < n
    void add(int x, LL y) {
        for (++x; x <= n; x += x & -x) {
            sums[x - 1] = Mod(sums[x - 1] + y);
        }
    }
    // sum 统计位置 0 到 位置 x 的总和
    // 0 <= x < n
    LL sum(int x) {
        LL ans = 0;
        for (++x; x; x -= x & -x) {
            ans = Mod(ans + sums[x - 1]);
        }
        return ans;
    }

    LL Mod(LL raw) {
        return (raw % mod_ + mod_) % mod_;
    }
};

// 区间型树状数组：区间修改（一个区间同时增加x或减少x），单点查询
// 用差分实现
// BitTreeRange bt(100); // n = 100
class BitTreeRange {
    int n;
    BitTree bt;
public:
    explicit BitTreeRange(int n) : n(n), bt(n) {}

    // add 从位置 l 到位置 r 所有元素增加 incr（incr 可以是负数）
    void addRange(int l, int r, int incr) {
        bt.add(l, incr);
        if (r + 1 < n) {
            bt.add(r + 1, -incr);
        }
    }

    // query 查询位置 x 的值
    int query(int x) {
        return bt.sum(x);
    }
};

// 区间映射树状数组：将大范围的数据压缩到小范围中。需要预先提供可能出现的数据。
class BitTreeMap {
    unordered_map<int, int> b2l;
    vector<int> l2b;
    BitTree bt;
public:
    // BitTreeMap 将一个大范围的数据（1e9）压缩到小范围（1e6）中
    explicit BitTreeMap(const vector<int> &a): bt(a.size()) {
        // BitTreeMap 初始化一个数值映射
        set<int> as{a.begin(), a.end()};
        l2b.resize(as.size());
        int l2bi = 0;
        for (auto x : as) {
            l2b[l2bi] = x;
            b2l[x] = l2bi;
            l2bi++;
        }
    }

    void add(int x, int y) {
        bt.add(b2l[x], y);
    }

    // 统计 0~x 的数 (0 <= x < n)
    int sum(int x) {
        auto ite = --std::upper_bound(l2b.begin(), l2b.end(), x);
        return bt.sum(ite - l2b.begin());
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

    BitTreeRange btr(100);
    btr.addRange(1, 98, 3);
    btr.addRange(2, 99, 4);
    cout << btr.query(0) << endl; // 0
    cout << btr.query(1) << endl; // 3
    cout << btr.query(98) << endl; // 7
    cout << btr.query(99) << endl; // 4
    return 0;
}
