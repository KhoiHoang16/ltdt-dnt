#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define FI "EULER_CYCLE.INP"
#define FO "EULER_CYCLE.OUT"

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

bool isEulerianCycle(const vector<vector<int>>& a){
    if(!connected_ignoring_isolated(a)) return false;
    vector<int> deg = degree_of(a);
    for(int u=1;u<=n;++u) if(deg[u]%2) return false;
    return true;
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
    // path là chu trình theo thứ tự ngược do thuật toán; in ra như vậy vẫn hợp lệ
    return path;
}

void solve(){
    cin >> n;
    mtke.assign(n+1, vector<int>(n+1,0));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin >> mtke[i][j];

    bool ok = isEulerianCycle(mtke);
    cout << (ok?1:0) << "\n";
    if(ok){
        int s = first_vertex_with_edge(mtke);
        vector<int> cyc = hierholzer(mtke, s);
        for(size_t i=0;i<cyc.size();++i){
            if(i) cout << ' ';
            cout << cyc[i];
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
