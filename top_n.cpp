//
// Created by jyh on 2月6日.
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;

template<typename T, typename Compare = std::less<T>>
class TopN {
    int n;
    multiset<T, Compare> left, chosen;
public:
    TopN(int nn): n(nn){}

    // add 添加一个元素 x
    virtual void add(T x) {
        insertIntoChosen(x);
        if (chosen.size() > n) {
            auto moveVal = *chosen.begin();
            removeFromChosen(moveVal);
            insertIntoLeft(moveVal);
        }
    }

    // remove 移除一个元素 x
    virtual void remove(T x) {
        if (left.find(x) != left.end()) {
            removeFromLeft(x);
            return;
        }
        removeFromChosen(x);
        if (chosen.size() < n && left.size() > 0) {
            auto moveVal = *(--left.end());
            removeFromLeft(moveVal);
            insertIntoChosen(moveVal);
        }
    }

    virtual void insertIntoChosen(T x) {
        chosen.insert(x);
    }
    virtual void removeFromChosen(T x) {
        chosen.erase(chosen.find(x));
    }
    virtual void insertIntoLeft(T x) {
        left.insert(x);
    }
    virtual void removeFromLeft(T x) {
        left.erase(left.find(x));
    }
};

// https://leetcode-cn.com/problems/minimum-difference-in-sums-after-removal-of-elements/
// 5987. 删除元素后和的最小差值

class MinN: public TopN<long long, greater<>> {
    long long chosenSum;
public:
    MinN(int nn): TopN(nn), chosenSum(0){}
    void add(long long x) {
        TopN::add(x);
    }
    virtual void insertIntoChosen(long long x) {
        TopN::insertIntoChosen(x);
        chosenSum += x;
    }
    virtual void removeFromChosen(long long x) {
        TopN::removeFromChosen(x);
        chosenSum -= x;
    }
    long long getChosenSum() {
        return chosenSum;
    }
};

class MaxN: public TopN<long long> {
    long long chosenSum;
public:
    MaxN(int nn): TopN(nn), chosenSum(0){}
    void add(long long x) {
        TopN::add(x);
    }
    virtual void insertIntoChosen(long long x) {
        TopN::insertIntoChosen(x);
        chosenSum += x;
    }
    virtual void removeFromChosen(long long x) {
        TopN::removeFromChosen(x);
        chosenSum -= x;
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
        long long ans = preAns[n / 3 - 1] + sufAns[n / 3];
        for (int i = n / 3; i < n - n / 3; i++) {
            ans = min(ans, preAns[i] - sufAns[i + 1]);
        }
        return ans;
    }
};

int main() {
    vector<int> nums{7,9,5,8,1,3};
    // vector<int> nums{3,1,2};
    cout << Solution().minimumDifference(nums) << endl;
    return 0;
}

