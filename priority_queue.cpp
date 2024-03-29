//
// priority_queue.cpp
//
// 优先队列（自定义比较函数 via 仿函数 Functor ）
//
// Created by jyh on 12月18日.
//

#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

// https://leetcode-cn.com/problems/minimum-difference-in-sums-after-removal-of-elements/
// 5987. 删除元素后和的最小差值

class MinN {
    int n;
    long long chosenSum;
    // priority_queue<int, vector<int>, less<int>> pq;
    // 大数先出
    struct compare {
        bool operator()(const int &n1, const int &n2) {
            return n1 < n2;
        }
    };
    priority_queue<int, vector<int>, compare> pq;
public:
    MinN(int nn): n(nn), chosenSum(0){}
    void add(int x) {
        pq.push(x);
        chosenSum += (long long)x;
        if (pq.size() > n) {
            auto removeVal = pq.top();
            pq.pop();
            chosenSum -= removeVal;
        }
    }
    long long getChosenSum() {
        return chosenSum;
    }
};

class MaxN {
    int n;
    long long chosenSum;
    // priority_queue<int, vector<int>, greater<int>> pq;
    // 小数先出
    struct compare {
        bool operator()(const int &n1, const int &n2) {
            return n1 > n2;
        }
    };
    priority_queue<int, vector<int>, compare> pq;
public:
    MaxN(int nn): n(nn), chosenSum(0){}
    void add(long long x) {
        pq.push(x);
        chosenSum += (long long)x;
        if (pq.size() > n) {
            auto removeVal = pq.top();
            pq.pop();
            chosenSum -= removeVal;
        }
    }
    long long getChosenSum() {
        return chosenSum;
    }
};

class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int n = nums.size();
        MinN pre(n / 3);
        MaxN suf(n / 3);
        vector<long long> preAns(n); // [i]: 从[0]~[i]
        vector<long long> sufAns(n); // [i]: 从[i]~[n - 1]
        for (int i = 0; i < n; i++) {
            pre.add(nums[i]);
            preAns[i] = pre.getChosenSum();
        }
        for (int i = n - 1; i >= 0; i--) {
            suf.add(nums[i]);
            sufAns[i] = suf.getChosenSum();
        }
        long long ans = preAns[n / 3 - 1] - sufAns[n / 3];
        for (int i = n / 3; i < n - n / 3; i++) {
            ans = min(ans, preAns[i] - sufAns[i + 1]);
        }
        return ans;
    }
};

// ClosureSort 用闭包比较函数排序
class ClosureSort {
public:
    void Sort() {
        vector<vector<int>> coupons{{2,5},{1,6},{3,4}};
        function<bool(int, int)> compareRight = [&](int n1, int n2) -> bool {
            return coupons[n1][1] > coupons[n2][1];
        };
        priority_queue<int, vector<int>, decltype(compareRight)> pq(compareRight);
        for (int i = 0; i < coupons.size(); i++) {
            pq.push(i);
        }
        while (!pq.empty()) {
            auto index = pq.top();
            pq.pop();
            cout << coupons[index][0] << ", " << coupons[index][1] << endl;
        }
    }
};

int main() {
    ClosureSort().Sort();
    return 0;
}
