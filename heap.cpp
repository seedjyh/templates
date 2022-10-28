//
// Created by seedj on 2022/10/28/0028.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void checkMaxHeap(const vector<int> &arr) {
    vector<int> nums;
    for (auto x : arr) {
        nums.push_back(x);
    }
    make_heap(nums.begin(), nums.end());
    while (!nums.empty()) {
        // print heap top
        cout << nums.front() << endl;
        // pop heap top
        pop_heap(nums.begin(), nums.end());
        nums.pop_back();
    }
}

void checkMinHeap(const vector<int> &arr) {
    vector<int> nums;
    for (auto x : arr) {
        nums.push_back(x);
    }
    make_heap(nums.begin(), nums.end(), greater<>());
    while (!nums.empty()) {
        // print heap top
        cout << nums.front() << endl;
        // pop heap top
        pop_heap(nums.begin(), nums.end(), greater<>());
        nums.pop_back();
    }
}

void checkMaxHeapWithCompare(const vector<int> &arr) {
    vector<int> nums;
    for (auto x : arr) {
        nums.push_back(x);
    }
    auto comp = [](const int &a, const int &b) -> bool {
        return a < b; // 右侧是堆顶
    };
    make_heap(nums.begin(), nums.end(), comp);
    while (!nums.empty()) {
        // print heap top
        cout << nums.front() << endl;
        // pop heap top
        pop_heap(nums.begin(), nums.end(), comp);
        nums.pop_back();
    }
}

void checkMinHeapWithCompare(const vector<int> &arr) {
    vector<int> nums;
    for (auto x : arr) {
        nums.push_back(x);
    }
    auto comp = [](const int &a, const int &b) -> bool {
        return a > b; // 右侧是堆顶
    };
    make_heap(nums.begin(), nums.end(), comp);
    while (!nums.empty()) {
        // print heap top
        cout << nums.front() << endl;
        // pop heap top
        pop_heap(nums.begin(), nums.end(), comp);
        nums.pop_back();
    }
}

void pushAnsPopMaxHeap(const vector<int> &arr) {
    vector<int> nums;
    // make
    make_heap(nums.begin(), nums.end());
    // push all
    for (auto x : arr) {
        // push heap
        nums.push_back(x);
        push_heap(nums.begin(), nums.end());
    }
    // pop all
    while (!nums.empty()) {
        // print top
        auto x = nums.front();
        cout << x << endl;
        // pop heap top
        pop_heap(nums.begin(), nums.end());
        nums.pop_back();
    }
}

int main() {
    vector<int> arr{2, 1, 5, 4, 3};
    // checkMaxHeap(arr);
    // checkMinHeap(arr);
    // checkMaxHeapWithCompare(arr);
    // checkMinHeapWithCompare(arr);
    pushAnsPopMaxHeap(arr);
    return 0;
}