//
// topological_sort.cpp
//
// 拓扑排序
//
// Created by jyh on 12月18日.
//

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <queue>
using namespace std;

class TopologicalSorting {
    class Node {
    public:
        Node(int id) {
            this->id = id;
            this->prevCount = 0;
            this->next.clear();
        };
        int id;
        int prevCount;
        set<int> next;
    };

    map<int, Node *> id2node;
public:
    TopologicalSorting() {};

    void SetID(int id) {
        getNode(id);
    }

    void SetOrder(int before, int after) {
        Node *beforeNode = getNode(before);
        Node *afterNode = getNode(after);
        if (before == after) {
            return;
        }
        if (beforeNode->next.find(after) == beforeNode->next.end()) {
            afterNode->prevCount++;
            beforeNode->next.insert(after);
        }
    }

    Node *getNode(int id) {
        if (this->id2node.find(id) == id2node.end()) {
            this->id2node[id] = new Node(id);
        }
        return this->id2node[id];
    }

    int Size() const {
        return this->id2node.size();
    }

    vector<int> Sort() {
        vector<int> result;
        queue<int> noPrevNodes;
        // find nodes without prev
        for (auto ite : id2node) {
            if (ite.second->prevCount == 0) {
                noPrevNodes.push(ite.first);
            }
        }
        // start work
        while (!noPrevNodes.empty()) {
            int topNodeID = noPrevNodes.front();
            noPrevNodes.pop();
            result.push_back(topNodeID);
            Node *topNode = id2node[topNodeID];
            for (auto nextNodeID : topNode->next) {
                Node *nextNode = id2node[nextNodeID];
                nextNode->prevCount--;
                if (nextNode->prevCount == 0) {
                    noPrevNodes.push(nextNodeID);
                }
            }
            id2node.erase(topNodeID);
            delete topNode;
        }
        if (id2node.empty()) {
            return result;
        } else {
            return {};
        }
    }
};

int main() {
    TopologicalSorting ts;
    //  3 -- 1 -- 2
    //   \    \  /
    //     --- 4
    ts.SetOrder(3, 1);
    ts.SetOrder(3, 2);
    ts.SetOrder(1, 4);
    ts.SetOrder(1, 2);
    ts.SetOrder(4, 2);
    for (auto x : ts.Sort()) {
        cout << x << ",";
    }
    cout << endl;
    return 0;
}

