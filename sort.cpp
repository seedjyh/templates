//
// sort.cp
//
// 排序（自定义比较函数）
//
// Created by jyh on 12月18日.
//

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;

int main() {
    // comp 预期的顺序，较小的在前。和优先队列相反。
    auto comp = [](const PII &a, const PII &b) -> bool {
        return a.second < b.second; // .second 较**小**的，更靠近[0]。
    };
    vector<PII> array;
    array.push_back(PII(3,1));
    array.push_back(PII(1,3));
    array.push_back(PII(2,2));
    sort(array.begin(), array.end(), comp);
    for (auto &pii : array) {
        cout << pii.first << "," << pii.second << endl;
    }
    return 0;
}
