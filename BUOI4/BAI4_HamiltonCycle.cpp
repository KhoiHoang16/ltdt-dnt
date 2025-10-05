#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define FI "HAMILTON_CYCLE.INP"
#define FO "HAMILTON_CYCLE.OUT"

int n;
vector<vector<int>> mtke;

vector<int> cyc;
vector<int> used;

bool dfs_cycle(int k){ // đang điền cyc[k]
    if(k==n){
        return mtke[cyc[n-1]][cyc[0]] > 0; // khép vòng
    }
    for(int v=2; v<=n; ++v){ // cố định 1 ở vị trí đầu
        if(!used[v] && mtke[cyc[k-1]][v] > 0){
            used[v]=1; cyc[k]=v;
            if(dfs_cycle(k+1)) return true;
            used[v]=0;
        }
    }
    return false;
}

bool backtrack_ham_cycle(){
    cyc.assign(n,0);
    used.assign(n+1,0);
    cyc[0]=1; used[1]=1;
    return dfs_cycle(1);
}

void solve(){
    cin >> n;
    mtke.assign(n+1, vector<int>(n+1,0));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin >> mtke[i][j];

    bool ok = backtrack_ham_cycle();
    cout << (ok?1:0) << "\n";
    if(ok){
        for(int i=0;i<n;++i){
            if(i) cout << ' ';
            cout << cyc[i];
        }
        cout << ' ' << cyc[0] << "\n";
    }
}

int main(){
    freopen(FI,"rt",stdin);
    freopen(FO,"wt",stdout);
    solve();
    return 0;
}
