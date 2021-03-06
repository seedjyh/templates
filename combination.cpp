//
// combination.cpp
//
// 组合数模板
//
// Created by jyh on 12月18日.
//

#include <iostream>
#include <unordered_map>
using namespace std;

typedef long long LL;

// Combination 计算组合数，可以取模或不取模。存储重复计算的结果。
class Combination {
    LL mod;
    unordered_map<LL, LL> k2v;
public:
    // 不想取模时，mod 填 0
    Combination(LL mod = 0) {
        this->mod = mod;
    }
    // 计算从n中取m的种类数。
    LL calc(LL n, LL m) {
        if (n == m) {
            return 1;
        }
        if (n < m) {
            return 0;
        }
        if (m == 1) {
            return n;
        }
        if (m == 0) {
            return 1;
        }
        LL key = makeKey(n, m);
        auto ite = k2v.find(key);
        if (ite != k2v.end()) {
            return ite->second;
        }
        LL value = calc(n - 1, m) + calc(n - 1, m - 1);
        if (mod > 0) {
            value %= mod;
        }
        k2v[key] = value;
        return value;
    }
    static LL makeKey(LL n, LL m) {
        return (n << 32) | m;
    }
};

// calcCombination 直接计算n中取m的组合数（无法取模）。
LL calcCombination(LL n, LL m) {
    if (n < m) {
        return 0;
    }
    if (m > n - m) {
        m = n - m;
    }
    LL ans = 1;
    for (LL up = n - m + 1, down = 1; up <= n; ++up, ++down) {
        ans *= up;
        ans /= down;
    }
    return ans;
}

int main() {
    int n = 5;
    int MOD = 10;
    Combination comb;
    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << ", comb=" << comb.calc(n, i) << endl;
    }
    Combination modComb(MOD);
    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << ", modComb=" << modComb.calc(n, i) << endl;
    }
    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << ", calcCombination=" << calcCombination(n, i) << endl;
    }
    return 0;
}
