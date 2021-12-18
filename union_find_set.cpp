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
    int FindRootSize(int a) {
        return sizes[FindRoot(a)];
    }
    void Union(int a, int b) {
        if (FindRootSize(a) > FindRootSize(b)) {
            roots[FindRoot(b)] = FindRoot(a);
        } else {
            roots[FindRoot(a)] = FindRoot(b);
        }
    }
};

int main() {
    int n = 10;
    UnionFindSet ufs(n);
    ufs.Union(2, 5);
    ufs.Union(3, 6);
    ufs.Union(2, 3);
    for (int i = 0; i < n; i++) {
        cout << i << "->" << ufs.FindRoot(i) << endl;
    }
    return 0;
}
