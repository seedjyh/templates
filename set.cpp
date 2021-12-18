//
// set.cpp
//
// set和multiset自定义排序
//
// Created by jyh on 12月18日.
//

#include <set>
#include <iostream>
using namespace std;

typedef pair<int, int> PII;

int main() {
    // comp 预期的顺序，较小的在前。和优先队列相反。
    auto comp = [](const PII &a, const PII &b) -> bool {
        return a.second < b.second; // .second 较**小**的，更靠近[0]。
    };

    set<PII, decltype(comp)> piis(comp);
    piis.insert(PII(1,3));
    piis.insert(PII(2,2));
    piis.insert(PII(3,3)); // 已存在则不会再往里写
    for (auto ite : piis) {
        cout << "set:" << ite.first << "," << ite.second << endl;
    }

    multiset<PII, decltype(comp)> piims(comp);
    piims.insert(PII(1,3));
    piims.insert(PII(2,2));
    piims.insert(PII(3,3)); // 已存在也会再往里写
    for (auto ite : piims) {
        cout << "multiset:" << ite.first << "," << ite.second << endl;
    }
    return 0;
}

