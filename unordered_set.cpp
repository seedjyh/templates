//
// unordered_set.cpp
//
// unordered_set 和 unordered_multiset（自定义hash函数和比较函数）
//
// Created by jyh on 12月18日.
//


#include <unordered_set>
#include <iostream>

using namespace std;

typedef pair<int, int> PII;
class PIIHash {
public:
    size_t operator()(const PII &pii) const {
        return 1;
    };
};
class PIIEqual {
public:
    bool operator()(const PII &a, const PII &b) const {
        return a.second == b.second;
    }
};

int main() {
    unordered_set<PII, PIIHash, PIIEqual> piius; // PIIEqual 用于去重；hash值相等的元素可能出现多个。
    piius.insert(PII(1, 3));
    piius.insert(PII(2, 2));
    piius.insert(PII(3, 3)); // 已存在则不会再往里写
    for (auto ite: piius) {
        cout << "unordered_set:" << ite.first << "," << ite.second << endl;
    }

    unordered_multiset<PII, PIIHash, PIIEqual> piiums; // PIIEqual 用于去重；hash值相等的元素可能出现多个。
    piiums.insert(PII(1, 3));
    piiums.insert(PII(2, 2));
    piiums.insert(PII(3, 3)); // 已存在也会再往里写
    for (auto ite: piiums) {
        cout << "unordered_multiset:" << ite.first << "," << ite.second << endl;
    }
    return 0;
}
