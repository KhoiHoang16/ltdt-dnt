// dfs_kdq.cpp
#include <bits/stdc++.h>
using namespace std;
const char *FI="dfs_kdq.inp";
const char *FO="dfs_kdq.out";

int n, startv;
vector< set<int> > adj;
vector<int> visited;

void dfs_iter(int s, ofstream &fout){
    stack<int> st;
    st.push(s);
    while(!st.empty()){
        int u = st.top(); st.pop();
        if(!visited[u]){
            visited[u]=1;
            fout << u << " ";
            // push neighbors in reverse order to visit smallest first
            vector<int> tmp(adj[u].begin(), adj[u].end());
            for(auto it = tmp.rbegin(); it != tmp.rend(); ++it){
                if(!visited[*it]) st.push(*it);
            }
        }
    }
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
    dfs_iter(startv, fout);
    fout << "\n";
    return 0;
}
