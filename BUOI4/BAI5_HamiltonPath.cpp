#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define FI "HAMILTON_PATH.INP"
#define FO "HAMILTON_PATH.OUT"

int n;
vector<vector<int>> mtke;

vector<int> pathHP;
vector<int> usedHP;

bool dfs_path(int k){ // đã điền 0..k-1, đang điền path[k]
    if(k==n) return true;
    for(int v=1; v<=n; ++v){
        if(!usedHP[v] && mtke[pathHP[k-1]][v] > 0){
            usedHP[v]=1; pathHP[k]=v;
            if(dfs_path(k+1)) return true;
            usedHP[v]=0;
        }
    }
    return false;
}

bool backtrack_ham_path(){
    pathHP.assign(n,0);
    usedHP.assign(n+1,0);
    // thử mọi đỉnh bắt đầu
    for(int s=1; s<=n; ++s){
        fill(usedHP.begin(), usedHP.end(), 0);
        pathHP[0]=s; usedHP[s]=1;
        if(dfs_path(1)) return true;
    }
    return false;
}

void solve(){
    cin >> n;
    mtke.assign(n+1, vector<int>(n+1,0));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin >> mtke[i][j];

    bool ok = backtrack_ham_path();
    cout << (ok?1:0) << "\n";
    if(ok){
        for(int i=0;i<n;++i){
            if(i) cout << ' ';
            cout << pathHP[i];
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
