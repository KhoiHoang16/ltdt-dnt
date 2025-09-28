// lienthongdfs.cpp
#include <bits/stdc++.h>
using namespace std;
const char *FI="lienthongDFS.inp";
const char *FO="lienthongDFS.out";

int n, startv;
vector< set<int> > adj;
vector<int> visited;
vector<int> order;

void dfs(int u){
    visited[u]=1;
    order.push_back(u);
    for(int v: adj[u]) if(!visited[v]) dfs(v);
}

int main(){
    ifstream fin(FI);
    ofstream fout(FO);
    if(!fin||!fout) return 0;

    fin >> n >> startv;
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
    order.clear();
    dfs(startv);

    fout << order.size() << "\n";
    for(size_t i=0;i<order.size();++i){
        if(i) fout << " ";
        fout << order[i];
    }
    fout << "\n";
    return 0;
}
