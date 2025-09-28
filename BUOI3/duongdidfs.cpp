// duongdidfs.cpp
#include <bits/stdc++.h>
using namespace std;
const char *FI="duongdiDFS.inp";
const char *FO="duongdiDFS.out";

int n, sx, sy;
vector< set<int> > adj;
vector<int> visited, parent;

bool dfs_find(int u, int t){
    visited[u]=1;
    if(u==t) return true;
    for(int v: adj[u]) if(!visited[v]){
        parent[v]=u;
        if(dfs_find(v,t)) return true;
    }
    return false;
}

int main(){
    ifstream fin(FI);
    ofstream fout(FO);
    if(!fin||!fout) return 0;

    fin >> n >> sx >> sy;
    string line; getline(fin,line);
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

    visited.assign(n+1,0);
    parent.assign(n+1,-1);
    if(!dfs_find(sx, sy)){
        fout << "Khong co duong di\n";
    } else {
        vector<int> path;
        for(int cur=sy; cur!=-1; cur=parent[cur]) path.push_back(cur);
        reverse(path.begin(), path.end());
        fout << path.size() << "\n";
        for(size_t i=0;i<path.size();++i){
            if(i) fout << " ";
            fout << path[i];
        }
        fout << "\n";
    }
    return 0;
}
