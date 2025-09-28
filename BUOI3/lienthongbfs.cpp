// lienthongbfs.cpp
#include <bits/stdc++.h>
using namespace std;

const char *FI = "LIENTHONGBFS.INP";
const char *FO = "LIENTHONGBFS.OUT";

int n, startv;
vector< set<int> > adj;
vector<int> visited;

void bfs(int s, vector<int> &order){
    order.clear();
    queue<int> q;
    visited.assign(n+1, 0);
    visited[s] = 1;
    q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        order.push_back(u);
        for(int v: adj[u]){
            if(!visited[v]){
                visited[v]=1;
                q.push(v);
            }
        }
    }
}

int main(){
    ifstream fin(FI);
    ofstream fout(FO);
    if(!fin || !fout) return 0;

    fin >> n >> startv;
    string line; getline(fin, line); // consume endline

    adj.assign(n+1, {});
    for(int i=1;i<=n;i++){
        if(!getline(fin, line)) line="";
        istringstream iss(line);
        int v;
        while(iss >> v){
            if(v == -1) break;
            if(v>=1 && v<=n) adj[i].insert(v);
        }
    }

    vector<int> order;
    bfs(startv, order);

    fout << order.size() << "\n";
    for(size_t i=0;i<order.size();++i){
        if(i) fout << " ";
        fout << order[i];
    }
    fout << "\n";
    return 0;
}
