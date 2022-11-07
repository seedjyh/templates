//
// combination.cpp
//
// 组合数模板
//
// Created by jyh on 12月18日.
//

#include <iostream>
#include <vector>
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

// calcInv 计算 1~n 的逆元（返回一个长度 n + 1 的数组）
vector<LL> calcInv(LL n, LL mod) {
    vector<LL> ret(n + 1);
    ret[1] = 1;
    for (int i = 2; i <= n; i++) {
        ret[i] = (mod - mod / i) * ret[mod % i] % mod;
    }
    return ret;
}

// calcCombinationMod 直接计算 n 中取 m 的组合数（可以取模，模必须是素数）。
LL calcCombinationMod(LL n, LL m, LL mod) {
    if (n < m) {
        return 0;
    }
    if (m > n - m) {
        m = n - m;
    }
    LL ans = 1; // C(m, m)
    auto inv = calcInv(n, mod);
    for (LL i = m + 1; i <= n; i++) {
        // 计算 C(i, m)
        // C(i, m) = C(i - 1, m) * i / (i - m)
        ans = ans * i % mod * inv[i - m] % mod;
    }
    return ans;
}


typedef long long LL;

class CombinationInvMod {
    LL _mod;
    vector<LL> _inv; // inv[i] 表示 i 的逆元。
    vector<LL> _fact; // fact[i] 表示 i! (mod)
    vector<LL> _factInv; // factInv[i] 表示 i! 的逆元。
public:
    // CombinationInvMod 用于O(1)计算带模的组合数。
    // n 是最大的可能是基。
    explicit CombinationInvMod(int n, int mod) {
        _mod = mod;
        _inv = calcInv(n, mod);
        _fact = calcFact(n, mod);
        _factInv = calcFactInv(n, mod);
    }
    // Comb 从 n 中取 m
    LL Comb(int n, int m) {
        return MOD(MOD(_fact[n] * _factInv[m]) * _factInv[n - m]);
    }
private:
    LL MOD(LL raw) {
        return raw % _mod;
    }
    // calcInv 计算 1~n 的逆元（返回一个长度 n + 1 的数组）
    static vector<LL> calcInv(LL n, LL mod) {
        vector<LL> ret(n + 1);
        ret[1] = 1;
        for (int i = 2; i <= n; i++) {
            ret[i] = (mod - mod / i) * ret[mod % i] % mod;
        }
        return ret;
    }
    static vector<LL> calcFact(LL n, LL mod) {
        vector<LL> ret(n + 1);
        ret[0] = ret[1] = 1;
        for (int i = 2; i <= n; i++) {
            ret[i] = (ret[i - 1] * i % mod);
        }
        return ret;
    }
    // calcInv 计算 1! ~ n! 的逆元（返回一个长度 n + 1 的数组）
    static vector<LL> calcFactInv(LL n, LL mod) {
        LL factN = 1;
        for (int i = 2; i <= n; i++) {
            factN = factN * i % mod;
        }
        vector<LL> ret(n + 1);
        ret[n] = quickPow(factN, mod - 2, mod);
        for (int i = n - 1; i >= 1; i--) {
            ret[i] = ret[i + 1] * (i + 1) % mod;
        }
        ret[0] = 1;
        return ret;
    }
    // quickPow 快速幂 base ^ p (mod)
    static LL quickPow(LL base, LL p, LL mod) {
        if (p == 0) {
            return 1;
        }
        if (p == 1) {
            return base % mod;
        }
        LL tmp = quickPow(base, p / 2, mod);
        tmp = tmp * tmp % mod;
        if (p % 2 == 1) {
            tmp = (tmp * base) % mod;
        }
        return tmp;
    }
};

int main() {
    int n = 5;
    int MOD = 7;
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
    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << ", calcCombinationMod=" << calcCombinationMod(n, i, MOD) << endl;
    }
    CombinationInvMod cim(n, MOD);
    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << ", CombinationInvMod=" << cim.Comb(n, i) << endl;
    }
    return 0;
}
