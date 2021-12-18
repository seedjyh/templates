//
// unordered_map.cpp
//
// unordered_map 和 unordered_multimap（自定义hash函数和比较函数）
//
// Created by jyh on 12月19日.
//

#include <unordered_map>
#include <iostream>
#include <string>

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
    unordered_map<PII, string, PIIHash, PIIEqual> piium; // PIIEqual 用于去重；hash值相等的元素可能出现多个。
    piium.insert(pair<PII, string>(PII(1, 3), "a"));
    piium.insert(pair<PII, string>(PII(2, 2), "b"));
    piium.insert(pair<PII, string>(PII(3, 3), "c")); // 已存在则不会再往里写
    for (auto ite: piium) {
        cout << "unordered_map:" << ite.first.first << "," << ite.first.second << "->" << ite.second << endl;
    }
    
    unordered_multimap<PII, string, PIIHash, PIIEqual> piiumm; // PIIEqual 用于去重；hash值相等的元素可能出现多个。
    piiumm.insert(pair<PII, string>(PII(1, 3), "a"));
    piiumm.insert(pair<PII, string>(PII(2, 2), "b"));
    piiumm.insert(pair<PII, string>(PII(3, 3), "c")); // 已存在也会再往里写
    for (auto ite: piiumm) {
        cout << "unordered_multimap:" << ite.first.first << "," << ite.first.second << "->" << ite.second << endl;
    }
    return 0;
}
