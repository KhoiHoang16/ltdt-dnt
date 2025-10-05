#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define FI "EULER_CLASSIFY.INP"
#define FO "EULER_CLASSIFY.OUT"

int n;
vector<vector<int>> mtke;

vector<int> degree_of(const vector<vector<int>>& a){
    vector<int> deg(n+1,0);
    for(int u=1;u<=n;++u)
        for(int v=1;v<=n;++v)
            deg[u]+=a[u][v];
    return deg;
}

int first_vertex_with_edge(const vector<vector<int>>& a){
    for(int u=1;u<=n;++u)
        for(int v=1;v<=n;++v)
            if(a[u][v]) return u;
    return 1;
}

bool connected_ignoring_isolated(const vector<vector<int>>& a){
    vector<int> deg = degree_of(a);
    bool hasEdge=false;
    for(int u=1;u<=n;++u) if(deg[u]>0){ hasEdge=true; break; }
    if(!hasEdge) return true;

    int s = first_vertex_with_edge(a);
    deque<int> dq; dq.push_back(s);
    vector<int> vis(n+1,0); vis[s]=1;
    while(!dq.empty()){
        int u=dq.front(); dq.pop_front();
        for(int v=1;v<=n;++v){
            if(!vis[v] && a[u][v]>0){
                vis[v]=1; dq.push_back(v);
            }
        }
    }
    for(int u=1;u<=n;++u)
        if(deg[u]>0 && !vis[u]) return false;
    return true;
}

int classifyEuler(const vector<vector<int>>& a){
    if(!connected_ignoring_isolated(a)) return 0;
    vector<int> deg = degree_of(a);
    int odd=0;
    for(int u=1;u<=n;++u) if(deg[u]%2) ++odd;
    if(odd==0) return 2;       // chu trình Euler
    if(odd==2) return 1;       // đường Euler
    return 0;
}

void solve(){
    cin >> n;
    mtke.assign(n+1, vector<int>(n+1,0));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin >> mtke[i][j];
    cout << classifyEuler(mtke) << "\n";
}

int main(){
    freopen(FI,"rt",stdin);
    freopen(FO,"wt",stdout);
    solve();
    return 0;
}
