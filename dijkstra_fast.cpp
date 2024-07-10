#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
#define fi first
#define se second

const int N=100005;
int n, m, s;
int dist[N];
bool vis[N];
vector<PII> g[N];

void dijkstra(){
    dist[s]=0;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, s});
    while(!q.empty()){
        int node=q.top().se;
        q.pop();
        if(vis[node]) continue;
        vis[node]=true;
        for(auto &e: g[node]){
            int v=e.fi;
            int w=e.se;
            if(dist[v]>dist[node]+w){
                dist[v]=dist[node]+w;
                q.push({dist[v], v});
            }
        }
    }
}

int main(){
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0x00, sizeof vis);
    cin>>n>>m>>s;
    int x, y, w;
    while(m--){
        cin>>x>>y>>w;
        g[x].push_back({y, w});
    }

    dijkstra();
    for(int i=1; i<=n; ++i) cout<<dist[i]<<" ";

    return 0;
}
