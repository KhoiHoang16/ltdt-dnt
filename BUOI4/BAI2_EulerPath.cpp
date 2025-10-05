#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define FI "EULER_PATH.INP"
#define FO "EULER_PATH.OUT"

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

bool hasEulerPathExactly2Odd(const vector<vector<int>>& a, int &start){
    if(!connected_ignoring_isolated(a)) return false;
    vector<int> deg = degree_of(a);
    int odd=0; int s1=-1, s2=-1;
    for(int u=1;u<=n;++u){
        if(deg[u]%2){
            ++odd;
            if(s1==-1) s1=u; else s2=u;
        }
    }
    if(odd==2){ start=s1; return true; }
    return false;
}

vector<int> hierholzer(vector<vector<int>> a, int start){
    vector<int> path;
    deque<int> st; st.push_back(start);
    while(!st.empty()){
        int u=st.back();
        bool moved=false;
        for(int v=1;v<=n;++v){
            if(a[u][v]>0){
                st.push_back(v);
                a[u][v]--; a[v][u]--;
                moved=true;
                break;
            }
        }
        if(!moved){
            path.push_back(u);
            st.pop_back();
        }
    }
    // đảo lại để bắt đầu từ start đi tới cuối (đẹp hơn)
    for(size_t i=0, j=path.size()?path.size()-1:0; i<j; ++i, --j)
        swap(path[i], path[j]);
    return path;
}

void solve(){
    cin >> n;
    mtke.assign(n+1, vector<int>(n+1,0));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin >> mtke[i][j];

    int s=-1;
    bool ok = hasEulerPathExactly2Odd(mtke, s);
    cout << (ok?1:0) << "\n";
    if(ok){
        vector<int> path = hierholzer(mtke, s);
        for(size_t i=0;i<path.size();++i){
            if(i) cout << ' ';
            cout << path[i];
        }
        cout << "\n";
    }
}

int main(){
    freopen(FI,"rt",stdin);
    freopen(FO,"wt",stdout);
    solve();
    return 0;
}
