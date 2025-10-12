#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL<<60);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    if(!(cin>>n>>m)) return 0;

    vector<vector<long long>> d(n, vector<long long>(n, INF));
    for (int i = 0; i < n; ++i) d[i][i] = 0;

    for(int i=0;i<m;++i){
        int u,v,w; cin>>u>>v>>w;
        --u; --v;
        d[u][v] = min<long long>(d[u][v], w);
        d[v][u] = min<long long>(d[v][u], w); // vô hướng
    }

    for(int k=0;k<n;++k)
        for(int i=0;i<n;++i)
            if (d[i][k] < INF/2)
                for(int j=0;j<n;++j)
                    if (d[k][j] < INF/2)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if (j) cout << ' ';
            if (d[i][j] >= INF/2) cout << "INF";
            else cout << d[i][j];
        }
        cout << "\n";
    }
    return 0;
}
