// dothiphandoi.cpp
#include <bits/stdc++.h>
using namespace std;
const char *FI="dothiphandi.inp";
const char *FO="dothiphandi.out";

int n;
vector< set<int> > adj;
vector<int> color;

bool dfs_color(int u, int c){
    color[u]=c;
    for(int v: adj[u]){
        if(color[v]==-1){
            if(!dfs_color(v,1-c)) return false;
        } else if(color[v]==c) return false;
    }
    return true;
}

int main(){
    ifstream fin(FI);
    ofstream fout(FO);
    if(!fin||!fout) return 0;

    fin >> n;
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

    color.assign(n+1,-1);
    for(int i=1;i<=n;i++){
        if(color[i]==-1){
            if(!dfs_color(i,0)){
                fout << "Do thi khong phan doi\n";
                return 0;
            }
        }
    }
    fout << "Do thi phan doi\n";
    return 0;
}
