//
// priority_queue.cpp
//
// 优先队列（自定义比较函数）
//
// Created by jyh on 12月18日.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

int main() {
    // comp 是否要交换顺序
    auto comp = [](const PII &a, const PII &b) -> bool {
        return a.second < b.second; // 把 .second 较大的，更靠近[0]，先出队列。
    };
    priority_queue<PII, vector<PII>, decltype(comp)> pq(comp);
    pq.push(PII(3,1));
    pq.push(PII(1,3));
    pq.push(PII(2,2));
    while (!pq.empty()) {
        auto now = pq.top();
        pq.pop();
        cout << now.first << "," << now.second << endl;
    }
    return 0;
}
