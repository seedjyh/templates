//
// union_find_set.cpp
//
// 并查集
//
// Created by jyh on 12月19日.
//

#include <vector>
#include <iostream> // for iota(,,)
#include <numeric>
using namespace std;

class UnionFindSet {
    vector<int> roots; // 每个节点的所属集合
    vector<int> sizes; // 每个集合的当前数量
public:
    // 创建并查集，这里 n 是节点数，节点编号 0 ~ n-1
    explicit UnionFindSet(int n): roots(n), sizes(n, 1) {
        iota(roots.begin(), roots.end(), 0);
    }
    int FindRoot(int a) {
        if (roots[a] == a) {
            return a;
        } else {
            roots[a] = FindRoot(roots[a]);
            return roots[a];
        }
    }
    // FindRootSize 返回 a 所在集合的大小（a不一定是根）
    int FindRootSize(int a) {
        return sizes[FindRoot(a)];
    }
    // FindRootSize 返回 a 所在集合的根
    void Union(int a, int b) {
        int bRoot = FindRoot(b);
        int aRoot = FindRoot(a);
        if (aRoot == bRoot) {
            return;
        }
        if (FindRootSize(aRoot) > FindRootSize(bRoot)) {
            sizes[aRoot] += sizes[bRoot];
            roots[bRoot] = aRoot;
        } else {
            sizes[bRoot] += sizes[aRoot];
            roots[aRoot] = bRoot;
        }
    }
};

int main() {
    int n = 10;
    UnionFindSet ufs(n);
    ufs.Union(2, 5);
    ufs.Union(3, 6);
    ufs.Union(2, 3);
    ufs.Union(8, 9);
    for (int i = 0; i < n; i++) {
        cout << "i=" << i << ", root=" << ufs.FindRoot(i) << ", size=" << ufs.FindRootSize(i) << endl;
    }
    return 0;
}
