#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <functional>
#include <unordered_map>
#include <climits>
#include <unordered_set>
#include <numeric>
#include <sstream>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;

class PrimMST {
    int n;
    vector<PII> edgeNode;
    vector<LL> edgeWeight;
    vector<vector<int>> adj;
public:
    explicit PrimMST(int _n): n(_n), adj(_n) {
        // n 是节点数
    }
    void addEdge(int u, int v, LL w) {
        // u, v 是节点下标（从 0 开始）
        int ei = edgeNode.size();
        edgeNode.push_back({u,v});
        edgeWeight.push_back(w);
        adj[u].push_back(ei);
        adj[v].push_back(ei);
    }
    vector<PII> span() {
        // span 返回最小生成树的边（的两个节点）
        vector<bool> used(n);
        auto cmp = [&](int a, int b) -> bool{
            return edgeWeight[a] > edgeWeight[b];
        };
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

        auto addNode = [&](int idx) -> void {
            if (used[idx]) return;
            used[idx] = true;
            for (auto &ei : adj[idx]) {
                int u = edgeNode[ei].first;
                int v = edgeNode[ei].second;
                int other = u + v - idx;
                if (used[other]) continue;
                pq.push(ei);
            }
        };

        vector<PII> ans;
        addNode(0);
        while (!pq.empty()) {
            auto ei = pq.top();
            pq.pop();
            if (used[edgeNode[ei].first] && used[edgeNode[ei].second]) continue;
            ans.push_back(edgeNode[ei]);
            addNode(edgeNode[ei].first);
            addNode(edgeNode[ei].second);
        }
        return ans;
    }
};

class AcAbc282E {
public:
    LL solve(const vector<int> &a, LL mod) {
        auto MOD = [&](LL raw) -> LL {
            return (raw % mod + mod) % mod;
        };
        function<LL(LL, LL)> modPow = [&](LL base, LL index) -> LL {
            if (index == 0) return 1;
            else if (index == 1) return MOD(base);
            auto halfRet = modPow(base, index / 2);
            auto ret = MOD(halfRet * halfRet);
            if (index & 1) {
                ret = MOD(ret * base);
            }
            return ret;
        };
        int n = a.size();
        PrimMST prime(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                auto tmp = MOD(modPow(a[i], a[j]) + modPow(a[j], a[i]));
                prime.addEdge(i, j, -tmp);
            }
        }
        LL ans = 0;
        for (auto [u, v] : prime.span()) {
            ans += MOD(modPow(a[u], a[v]) + modPow(a[v], a[u]));
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    // 全都用 cin 输入，cout 输出。
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    cout << AcAbc282E().solve(a, m) << endl;
    return 0;
}
