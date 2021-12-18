//
// lower_bound.cpp
//
// lower_bound、upper_bound用于vector
//
// Created by jyh on 12月18日.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums{1,2,2,4,5};
    for (int i = 0; i <= 6; i++) {
        // lower_bound 找到 >= i 的最小值位置
        // upper_bound 找到 > i 的最小值位置
        cout << i << ": lower_bound_index=" << std::lower_bound(nums.begin(), nums.end(), i) - nums.begin() <<
                     ", upper_bound_index=" << std::upper_bound(nums.begin(), nums.end(), i) - nums.begin() <<endl;
    }
    return 0;
}
