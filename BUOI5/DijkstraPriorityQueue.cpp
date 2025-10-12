#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL<<60);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,s,t;
    if(!(cin>>n>>m>>s>>t)) return 0;

    vector<vector<pair<int,int>>> adj(n+1);
    for(int i=0;i<m;++i){
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    vector<long long> dist(n+1, INF);
    vector<int> par(n+1, -1);
    using P = pair<long long,int>;
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[s]=0; pq.push({0,s});
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

    if (dist[t] >= INF/2){
        cout << "-1 -1\n\n";
        return 0;
    }

    vector<int> path;
    for(int v=t; v!=-1; v=par[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << (int)path.size() << " " << dist[t] << "\n";
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
