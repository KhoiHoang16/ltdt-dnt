// thanhphanbfs.cpp
#include <bits/stdc++.h>
using namespace std;

const char *FI = "THANHPHANBFS.INP";
const char *FO = "THANHPHANBFS.OUT";

int n;
vector< set<int> > adj;
vector<int> visited;

vector<int> bfs_comp(int s){
    vector<int> comp;
    queue<int> q;
    visited[s]=1; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        comp.push_back(u);
        for(int v: adj[u]){
            if(!visited[v]) { visited[v]=1; q.push(v); }
        }
    }
    sort(comp.begin(), comp.end());
    return comp;
}

int main(){
    ifstream fin(FI);
    ofstream fout(FO);
    if(!fin || !fout) return 0;

    fin >> n;
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

    visited.assign(n+1, 0);
    vector<vector<int>> comps;
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            comps.push_back(bfs_comp(i));
        }
    }

    sort(comps.begin(), comps.end(), [](const vector<int>&a,const vector<int>&b){
        if(a.empty() || b.empty()) return a.size()<b.size();
        return a[0]<b[0];
    });

    fout << comps.size() << "\n";
    for(auto &c: comps){
        for(size_t i=0;i<c.size();++i){
            if(i) fout << " ";
            fout << c[i];
        }
        fout << "\n";
    }
    return 0;
}
