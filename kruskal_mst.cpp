//
// Created by jyh on 2022/12/31.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

// 并查集
class UnionFindSet {
    vector<int> roots; // 每个节点的所属集合
    vector<int> sizes; // 每个集合的当前数量
public:
    // 创建并查集，这里 n 是节点数，节点编号 0 ~ n-1
    explicit UnionFindSet(int n) : roots(n), sizes(n, 1) {
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

class Kruskal {
public:
    Kruskal() {}

    class MST {
    public:
        MST() : connected(false), totalWeight(0) {};
        bool connected;
        long long totalWeight;
        vector<int> chosenEdges;
    };

    // findMST 查找最小生成树。
    // n = 节点数
    // edges = 边集，每条边(u, v, w) 其中 u, v 是节点，从 1 开始编号，w 是边权。
    // 返回：如果图不连通，则返回空集。
    // 被选中的边的下标列表，不保证顺序。边的下标就是edges里的下标，从0开始。
    MST findMST(int n, const vector<vector<int>> &edges) {
        vector<int> ei(edges.size());
        for (int i = 0; i < ei.size(); i++) {
            ei[i] = i;
        }

        auto comp = [&](const int &a, const int &b) -> bool {
            return edges[a][2] < edges[b][2];
        };
        sort(ei.begin(), ei.end(), comp);

        UnionFindSet ufs(n + 1);

        MST mst;
        for (int i = 0; i < ei.size(); i++) {
            int u = edges[ei[i]][0];
            int v = edges[ei[i]][1];
            int w = edges[ei[i]][2];
            if (ufs.FindRoot(u) != ufs.FindRoot(v)) {
                mst.chosenEdges.push_back(ei[i]);
                mst.totalWeight += w;
                ufs.Union(u, v);
            }
        }

        mst.connected = true;
        for (int i = 1; i <= n; i++) {
            if (ufs.FindRoot(i) != ufs.FindRoot(1)) {
                return MST();
            }
        }
        return mst;
    };
};

int main() {
    int n = 4;
    vector<vector<int>> edges{{1, 2, 3},
                              {1, 3, 1},
                              {2, 3, 2},
                              {3, 4, 4}};
    auto mst = Kruskal().findMST(n, edges);
    cout << "connected=" << mst.connected << endl;
    cout << "totalWeight=" << mst.totalWeight << endl;
    for (auto ei: mst.chosenEdges) {
        cout << edges[ei][0] << ", " << edges[ei][1] << endl;
    }
    return 0;
}