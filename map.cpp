//
// set.cpp
//
// set和multiset自定义排序
//
// Created by jyh on 12月18日.
//

#include <map>
#include <string>
#include <iostream>
using namespace std;

typedef pair<int, int> PII;

int main() {
    // comp 预期的顺序，较小的在前。和优先队列相反。
    auto comp = [](const PII &a, const PII &b) -> bool {
        return a.second < b.second; // .second 较**小**的，更靠近[0]。
    };

    map<PII, string, decltype(comp)> piim(comp);
    piim.insert(pair<PII, string>(PII(1,3), string("a")));
    piim.insert(pair<PII, string>(PII(2,2), string("b")));
    piim.insert(pair<PII, string>(PII(3,3), string("c"))); // 已存在则不会再往里写
    for (auto ite : piim) {
        cout << "map:" << ite.first.first << "," << ite.first.second << ":" << ite.second << endl;
    }

    multimap<PII, string, decltype(comp)> piimm(comp);
    piimm.insert(pair<PII, string>(PII(1,3), string("a")));
    piimm.insert(pair<PII, string>(PII(2,2), string("b")));
    piimm.insert(pair<PII, string>(PII(3,3), string("c"))); // 已存在则不会再往里写
    for (auto ite : piimm) {
        cout << "multimap:" << ite.first.first << "," << ite.first.second << ":" << ite.second << endl;
    }
    return 0;
}

