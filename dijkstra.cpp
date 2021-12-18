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
    void add(int u, int v, const WEIGHT &w) {
        this->pair2index[make_pair(u, v)] = this->weights.size();
        this->weights.push_back(w);
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

// 需要PairMap保存边。
// 调用顺序：
// 1 - Dijkstra(n)
// 2 - addEdge 所有边
// 3 - calc() 执行dijkstra算法。
// 4 - getDistance / getPrev
class Dijkstra {
    int nodeCount; // 节点数
    // 邻接表
    vector<vector<int>> adjacentNodes; // [i]和节点i邻接的节点的下标。
    vector<int> distance; // [i]从源到节点i的最短路长度。
    vector<int> prev; // [i]从源到节点i的最短路径上，节点i的前一个节点的下标。-1表示没有或不知道前一个节点。
    vector<bool> visited; // [i]是否已求出从源到节点i的最短路。也可视为“是否在集合S中”。
    // 边
    PairMap<int> edges;
public:
    // n是节点的数量。
    Dijkstra(int n) :
            nodeCount(n),
            adjacentNodes(n) {};

    // 添加一条边，0 <= u、v < nodeCount
    void addEdge(int u, int v, int weight) {
        adjacentNodes[u].push_back(v);
        edges.add(u, v, weight);
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
            int weight;

            bool operator<(const EdgeInQueue &other) const {
                return this->weight > other.weight;
            }
        };
        priority_queue <EdgeInQueue> edgeQueue; // pair<边权, 未进S的节点下标>
        // S设成空集
        distance.resize(nodeCount, INT_MAX);
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
    const vector<int> &getDistance() const {
        return this->distance;
    }

    // 获取各节点单源最短路的上一个节点。
    const vector<int> &getPrev() const {
        return this->prev;
    }
};

int main() {
    Dijkstra d(4);
    d.addEdge(0, 2, 1);
    d.addEdge(0, 1, 7);
    d.addEdge(2, 3, 9);
    d.addEdge(2, 1, 2);
    d.addEdge(1, 3, 3);
    d.calc(0);
    for (auto dis : d.getDistance()) {
        cout << "distance:" << dis << endl;
    }
    for (auto prev : d.getPrev()) {
        cout << "prev:" << prev << endl;
    }
    return 0;
}
