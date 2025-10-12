#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL<<60);

struct Node { long long d; int p; };

pair<vector<long long>, vector<int>> dijkstra(int n, int s, const vector<vector<pair<int,int>>>& adj){
    vector<long long> dist(n+1, INF);
    vector<int> par(n+1, -1);
    using P = pair<long long,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[s] = 0; pq.push({0, s});
    while(!pq.empty()){
        auto [du,u]=pq.top(); pq.pop();
        if (du!=dist[u]) continue;
        for(auto [v,w]: adj[u]){
            if(dist[v] > du + w){
                dist[v] = du + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return {dist, par};
}

vector<int> build_path(int t, const vector<int>& par){
    vector<int> path;
    if (t==-1) return path;
    for (int v=t; v!=-1; v=par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,s,t,x;
    if(!(cin>>n>>m>>s>>t>>x)) return 0;

    vector<vector<pair<int,int>>> adj(n+1);
    for(int i=0;i<m;++i){
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    auto [d1,p1] = dijkstra(n, s, adj);
    auto [d2,p2] = dijkstra(n, x, adj);

    if (d1[x] >= INF/2 || d2[t] >= INF/2){
        cout << "-1 -1\n\n";
        return 0;
    }

    auto path1 = build_path(x, p1);       // s -> ... -> x
    auto path2 = build_path(t, p2);       // x -> ... -> t

    // nối, bỏ trùng đỉnh x
    vector<int> path = path1;
    for (size_t i = 1; i < path2.size(); ++i) path.push_back(path2[i]);

    cout << (int)path.size() << " " << (d1[x] + d2[t]) << "\n";
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
