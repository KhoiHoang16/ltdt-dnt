// canhcau.cpp
#include <bits/stdc++.h>
using namespace std;

const char *FI = "canhcau.inp";
const char *FO = "canhcau.out";

int n, x, y, z;
vector< set<int> > adj;

int count_components(const vector< set<int> > &g){
    int N = (int)g.size()-1;
    vector<int> vis(N+1,0);
    int cnt=0;
    for(int i=1;i<=N;i++){
        if(!vis[i]){
            cnt++;
            queue<int> q; q.push(i); vis[i]=1;
            while(!q.empty()){
                int u=q.front(); q.pop();
                for(int v: g[u]) if(!vis[v]){
                    vis[v]=1; q.push(v);
                }
            }
        }
    }
    return cnt;
}

int main(){
    ifstream fin(FI);
    ofstream fout(FO);
    if(!fin || !fout) return 0;

    fin >> n >> x >> y >> z;
    string line; getline(fin, line);

    adj.assign(n+1,{});
    for(int i=1;i<=n;i++){
        if(!getline(fin,line)) line="";
        istringstream iss(line);
        int v;
        while(iss>>v){
            if(v==-1) break;
            if(v>=1 && v<=n) adj[i].insert(v);
        }
    }

    int orig = count_components(adj);

    auto g1 = adj;
    g1[x].erase(y);
    g1[y].erase(x);
    int c1 = count_components(g1);
    if(c1>orig) fout << "canh cau\n"; else fout << "khong la canh cau\n";

    auto g2 = adj;
    for(int i=1;i<=n;i++) g2[i].erase(z);
    g2[z].clear();
    int c2 = count_components(g2);
    if(c2>orig) fout << "dinh khop\n"; else fout << "khong la dinh khop\n";

    return 0;
}
