//
// dijkstra.cpp
//
// 有向图 dijkstra 算法
//
// Created by jyh on 12月19日.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

// 邻接矩阵的紧凑表达
template<typename WEIGHT>
class PairMap {
    struct pairHash {
        size_t operator()(const pair<int, int> &p) const {
            return (static_cast<size_t>(p.first) << 32u) | static_cast<size_t>(p.second);
        }
    };

    // 从节点对到边下标的映射
    unordered_map<pair<int, int>, int, pairHash> pair2index;
    // 从边下标到边权的映射
    vector<WEIGHT> weights;
public:
    // n 比最大的节点下标还要大1。
    PairMap() {}

    // 添加一个pair->value映射。不考虑重复pair的情况。
    // u < n, v < n, weights >= 0
    void add(int u, int v, const WEIGHT w) {
        this->pair2index[make_pair(u, v)] = this->weights.size();
        this->weights.push_back(w);
    }

    // 更新一个pair->value映射。如果pair重复，则保存最小的那个权。
    // u < n, v < n, weights >= 0
    void update(int u, int v, const WEIGHT w) {
        auto ite = pair2index.find(make_pair(u, v));
        if (ite == pair2index.end()) {
            this->pair2index[make_pair(u, v)] = this->weights.size();
            this->weights.push_back(w);
        } else {
            this->weights[ite->second] = min(this->weights[ite->second], w);
        }
    }

    // 查询从u到v的边下标，如果没有则返回-1。
    int getIndex(int u, int v) {
        auto ite = this->pair2index.find(make_pair(u, v));
        if (ite == this->pair2index.end()) {
            return -1;
        } else {
            return ite->second;
        }
    }

    const WEIGHT &getWeight(int index) {
        return this->weights[index];
    }
};

// 优先队列 dijkstra 的复杂度是 O(mlogm) 这里 m 是边的数量。所以只能用于稀疏图。稠密图要用朴素 dijkstra，复杂度 O(n^2)
// 需要PairMap保存边。
// 调用顺序：
// 1 - Dijkstra(n)
// 2 - addEdge 所有边
// 3 - calc() 执行dijkstra算法。
// 4 - getDistance / getPrev
template<typename WEIGHT>
class Dijkstra {
    int nodeCount; // 节点数
    // 邻接表
    vector<vector<int>> adjacentNodes; // [i]和节点i邻接的节点的下标。
    vector<WEIGHT> distance; // [i]从源到节点i的最短路长度。
    vector<int> prev; // [i]从源到节点i的最短路径上，节点i的前一个节点的下标。-1表示没有或不知道前一个节点。
    vector<bool> visited; // [i]是否已求出从源到节点i的最短路。也可视为“是否在集合S中”。
    // 边
    PairMap<WEIGHT> edges;
    // 无穷大
    const WEIGHT infinite;
public:
    // n是节点的数量。
    Dijkstra(int n, WEIGHT infinite = makeInfinite()) :
            nodeCount(n),
            adjacentNodes(n),
            infinite(infinite) {};

    // 添加一条边，0 <= u、v < nodeCount
    void addEdge(int u, int v, WEIGHT weight) {
        adjacentNodes[u].push_back(v);
        edges.update(u, v, weight); // 如果有重复边，选择权重最小的。
    }

    // 查询下标为node的节点的邻接节点
    const vector<int> &getAdjacent(int node) const {
        return adjacentNodes[node];
    }

    // 计算从节点s开始的单源最短路径。填充distance, prev和visited。
    void calc(int s) {
        // 边的优先队列
        class EdgeInQueue {
        public:
            int from; // S中的节点
            int to; // S外的节点
            WEIGHT weight;

            bool operator<(const EdgeInQueue &other) const {
                return this->weight > other.weight;
            }
        };
        priority_queue<EdgeInQueue> edgeQueue; // pair<边权, 未进S的节点下标>
        // S设成空集
        distance.resize(nodeCount, infinite);
        prev.resize(nodeCount, -1);
        visited.resize(nodeCount, false);
        // 开始计算！
        // 先将s放入S。
        distance[s] = 0; // 从s到s距离自然是0
        prev[s] = -1; // 从s到s的话没有前驱结点。
        visited[s] = true;
        for (auto adjNode: adjacentNodes[s]) {
            edgeQueue.push(EdgeInQueue{s, adjNode, edges.getWeight(edges.getIndex(s, adjNode))});
        }
        while (!edgeQueue.empty()) {
            auto e = edgeQueue.top();
            edgeQueue.pop();
            if (visited[e.to]) {
                continue;
            }
            // 将e.to添加到S中。
            distance[e.to] = e.weight;
            prev[e.to] = e.from;
            visited[e.to] = true;
            for (auto adjNode: adjacentNodes[e.to]) {
                if (visited[adjNode]) {
                    continue;
                }
                edgeQueue.push(EdgeInQueue{
                        e.to,
                        adjNode,
                        distance[e.to] + edges.getWeight(edges.getIndex(e.to, adjNode))
                });
            }
        }
    }

    // 获取各节点单源最短路的长度。
    // makeInfinite()表示不可达。
    const vector<WEIGHT> &getDistance() const {
        return this->distance;
    }

    // 获取各节点单源最短路的上一个节点。
    // -1表示没有上一个节点（可能是不可达，也可能是源节点）。
    const vector<int> &getPrev() const {
        return this->prev;
    }

    // 生成WEIGHT类型的最大值。也可用于判断是否不可达。
    static WEIGHT makeInfinite() {
        return ~((WEIGHT) 1 << (sizeof(WEIGHT) * 8 - 1));
    }
};

int main() {
    Dijkstra<int> d(5);
    d.addEdge(0, 2, 1);
    d.addEdge(0, 1, 7);
    d.addEdge(2, 3, 9);
    d.addEdge(2, 1, 2);
    d.addEdge(1, 3, 3);
    d.addEdge(4, 0, 1);
    d.calc(0);
    for (auto dis : d.getDistance()) {
        if (dis == d.makeInfinite()) {
            cout << "distance: infinite" << endl;
        } else {
            cout << "distance:" << dis << endl;
        }
    }
//    distance:0
//    distance:3
//    distance:1
//    distance:6
//    distance: infinite
    for (auto prev : d.getPrev()) {
        if (prev < 0) {
            cout << "prev: none" << endl;
        } else {
            cout << "prev:" << prev << endl;
        }
    }
//    prev: none
//    prev:2
//    prev:0
//    prev:1
//    prev: none
    return 0;
}
